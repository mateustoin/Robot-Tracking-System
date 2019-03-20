#include "scannercv.h"

//Includes das bibliotecas que serão utilizadas para a comunicação serial
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

scannerCv::scannerCv(QObject *parent) : QObject (parent)
{
    arduino_is_available = false; //Iniciando variável
    arduino_port_name = ""; //Iniciando variável com nada
    arduino = new QSerialPort; //Adicionado de acordo com o vídeo

    serialBuffer = "";
/*
 * CODIGO FEITO PARA DEBUGAR E DESCOBRIR VENDOR ID E PRODUCT ID DAS PORTAS DISPONÍVEIS.
 * IDEM PARA IDENTIFICAR QUANTOS DISPOSITIVOS ESTÃO DISPONÍVEIS NAS PORTAS SERIAIS
*/    //Para descobrir quantas portas estão conectadas na máquina
    qDebug() << "Número de portas disponíveis: " << QSerialPortInfo::availablePorts().length();

    //Verifica o arduino da porta (se for um arduino mesmo)
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){ //Vendor e Product ID está relacionado a venda do hardware ou algo relacionado á identificação dos produtos
        //PELO PRODUCT ID POR EXEMPLO CONSEGUIMOS DIFERENCIAR E IDENTIFICAR QUAL PLACA ESTÁ CONECTADA (UNO = 67, MEGA = 66)
        qDebug() << "Tem vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if (serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }

        qDebug() << "Tem product ID: " << serialPortInfo.hasProductIdentifier();
        if (serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }

        setVendorProductID(serialPortInfo.vendorIdentifier(), serialPortInfo.productIdentifier());
    }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_mega_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_mega_product_id){
                    arduino_port_name = serialPortInfo.portName(); // Se passar por todas as verificações recebe o nome da porta
                    arduino_is_available = true; // Se passar por todas as verificações recebe true na verificação
                }
            }
        }
    }

    //Agora que passou as verificações, vamos ao trabalho
    if (arduino_is_available){
        // Temos que abrir e configurar a porta serial
        /*
         * A SEGUIR ENCONTRAMOS AS CONFIGURAÇÕES RECOMENDADAS
         * LEMBRAR DE FAZÊ-LAS DEPOIS QUE ABRIR O ARDUINO (USAR ARDUINO->OPEN()), POIS FAZER ANTES NÃO FAZ SENTIDO
         * VISTO QUE ELES RETORNAM TRUE OU FALSE E SÓ SERVIRÁ DE ALGO QUANDO O ARDUINO ESTIVER ACESSÍVEL
         *
         * */
        arduino->setPortName(arduino_port_name); // Mudando o nome da porta para o que encontramos do arduino
        arduino->open(QSerialPort::ReadWrite); //Acessando arduino em modo de escrita para a placa, pois só iremos controlar os leds
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8); // Arduino, 8 bits, dãã
        arduino->setParity(QSerialPort::NoParity); // Descobrir depois o que está relacionado a isso!!!! <<<<<<<<<<<
        arduino->setStopBits(QSerialPort::OneStop); // A opção half and stop é só para o windows
        arduino->setFlowControl(QSerialPort::NoFlowControl); // Descobrir pra que diachos isso serve também!!! <<<<<<<

        //PARTICULARIDADE P/ LER DADOS
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial())); //Função será chamada sempre que tiver um valor disponível para leitura
        /*
         * Quando é conectado, a função do SIGNAL "readyRead" é usado quando tem informação na porta serial para ler
         * Mas não tem garantias de que a mensagem inteira está disponível
         * Então é necessário criar um buffer para a entrada
         * */

        qDebug() << "ARDUINO DISPONÍVEL NA PORTA: " << arduino->portName();

        scannerCv::qrcodeScanner();

    }else{
        // Exibe uma mensagem de erro se arduino não estiver disponível
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>QMessageBox::warning(this, "Erro na porta", "Não foi possível localizar o Arduino...");
        qDebug() << "ARDUINO NÃO ESTA DISPONIVEL!";
    }
}

void scannerCv::setVendorProductID(quint16 vendorId, quint16 productId){
    arduino_mega_vendor_id = vendorId;
    arduino_mega_product_id = productId;
}

void scannerCv::readSerial(){
    serialData = arduino->readAll();
    serialBuffer += QString::fromStdString(serialData.toStdString());

    QStringList bufferSplit = serialBuffer.split(",");
    qDebug() << serialBuffer;

    if (bufferSplit.length() < 3){
        serialData = arduino->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
    }else{
        //Dialog::updateLCD(bufferSplit[1]);
        m_sensorValue = bufferSplit[1];
        qDebug() << "ENTRA AQUI RAPAZINHO!";
        serialBuffer = "";
        //emit sensorReadChanged();
    }
}

void scannerCv::setPwmValue(const QString &pwmValue)
{
    //if (pwmValue == m_pwmValue)
    //    return;

    m_pwmValue = pwmValue;

    scannerCv::updateLED(pwmValue); // Imprime letra "c" antes do número, como esperado para mudar led individualmente
    //qDebug() << "Valor led3: " << pwmValue;

    //emit pwmValueChanged();

}

// Adicionando mais um método para a classe Dialog
void scannerCv::updateLED (QString comando)
{
    if(arduino->isWritable()){
        arduino->write(comando.toStdString().c_str());
        qDebug() << "Esta escrevendo! " << comando.toStdString().c_str();
    }else{
        qDebug() << "Não foi possível escrever na porta serial!";
    }
}

void scannerCv::qrcodeScanner()
{
    cv::VideoCapture cap;
        cap.open(0);
        if(!cap.isOpened()) {  // check if we succeeded
            //std::cout << "Failed to open input video: " << argv[1];
            //return -1;
            qDebug() << "Deu errado mano";
        }

        //cv::Mat img = cv::imread("/home/busta/git/zbar-code/examples/barcode.png");

        zbar::ImageScanner scanner;
        scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

        for(;;) {
            cv::Mat frame;
            cap >> frame; // get a new frame from camera
            if (frame.empty())
                break;

            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

            // wrap image data
            zbar::Image image(gray.cols, gray.rows, "Y800", gray.data, gray.rows * gray.cols);

            double t = (double)cv::getTickCount();
            // scan the image for barcodes
            scanner.scan(image);
            t = ((double)cv::getTickCount() - t)/ cv::getTickFrequency();
            // extract results
            for(zbar::Image::SymbolIterator symbol = image.symbol_begin();
                symbol != image.symbol_end(); ++symbol) {
                // do something useful with results
               //qDebug() << "decodificado " << symbol->get_type_name()
                //<< " Retorno \"" << symbol->get_data() << '"' << " em " << t * 1000 << "ms"  << endl;


                //AQUI COMEÇARIA A LÓGICA DE LEITURA DE STRINGS DO QRCODE
                istringstream bah(symbol->get_data());

                bah >> locAtual;
                bah >> proximo;
                bah >> anterior;
                int caminhoP = 0, caminhoN = 0;
                string melhorCaminho;

                for(int i=locAtual; i != LOCFINAL; --i){

                    if(i==0){
                        i=TOTALQRCODES;
                    }caminhoN++;
                }

                for(int i=locAtual; i != LOCFINAL; ++i){

                    if(i>TOTALQRCODES){
                        i=1;
                    }caminhoP++;
                }

                if(caminhoP > caminhoN){
                    melhorCaminho = anterior;
                    scannerCv::segueAnterior = true;
                }else{
                    melhorCaminho = proximo;
                    scannerCv::segueAnterior = false;
                }
                //cout << "Localizacao atual: " << locAtual << ", Comando para proximo local: " << proximo << ", Comando para local anterior: " << anterior << endl;
                if (locAtual != LOCFINAL){
                    qDebug() << "Você está no QrCod: " << locAtual << " e deve seguir o caminho: " << QString(melhorCaminho.c_str());

                    if (segueAnterior == true)
                        scannerCv::updateLED("a1");
                    else
                        scannerCv::updateLED("a0");
                }

                else{
                    qDebug() << "Já chegou no destino!";
                    scannerCv::updateLED("a255");
                    //QThread::msleep(1000);
                }

            }

            cv::imshow("frame", frame);
            int key = cv::waitKey(1);
            if(key == 'q')
                break;
        }
}
