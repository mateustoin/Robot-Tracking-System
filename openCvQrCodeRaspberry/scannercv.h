#ifndef SCANNERCV_H
#define SCANNERCV_H

#include <QString>
#include <QDebug>
#include <QSerialPort> //Incluindo biblioteca por causa da instância criada na classe
#include <QObject>

#include <QString>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>

#include <raspicam/raspicam_cv.h>
#include "camera.h"

#include <QThread>

/*
 * Valores referentes a quantidade de QrCodes presentes no ambiente e o ponto final de localização
 */
#define TOTALQRCODES 5
#define LOCFINAL 4 // Localização final

using namespace std;

class scannerCv : public QObject
{
    Q_OBJECT

public:
    explicit scannerCv(QObject *parent = nullptr);
    //scannerCv();

    void setVendorProductID(const quint16 vendorId, const quint16 productId);
    void setPwmValue(const QString &pwmValue);

    int locAtual, locProx; // Armazena localização atual quando ler o primeiro QrCode e seta próximo ponto
    string proximo, anterior, data;

    void qrcodeScanner();

    static void msleep(unsigned long msecs){QThread::msleep(msecs);}

private slots:
    void readSerial();

private:
    void updateLED (QString);

    QSerialPort *arduino;
    //Depois de identificar no debug o vendor e product ID
    quint16 arduino_mega_vendor_id;
    quint16 arduino_mega_product_id;
    QString arduino_port_name; // variável que vai receber o nome da porta que o arduino está conectado
    bool arduino_is_available; // booleano para comparar se o arduino ainda está conectado

    QString m_pwmValue;

    //Inicializando atributos para leitura da porta serial
    QString m_sensorValue;
    QByteArray serialData;
    QString serialBuffer;

    bool segueAnterior;
};

#endif // SCANNERCV_H
