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

    // Atualiza valores de vendorId e productId quando é chamado
    void setVendorProductID(const quint16 vendorId, const quint16 productId);

    int locAtual, locProx; // Armazena localização atual quando ler o primeiro QrCode e seta próximo ponto
    string proximo, anterior, data;

    // Método que faz a chamda das rotinas relacionadas ao opencv
    void qrcodeScanner();

private slots:
    void readSerial();

private:
    void updateLED (QString);

    QSerialPort *arduino;
    //Depois de identificar no debug o vendor e product ID
    quint16 vendorId;
    quint16 productId;
    QString arduino_port_name; // variável que vai receber o nome da porta que o arduino está conectado
    bool arduino_is_available; // booleano para comparar se o arduino ainda está conectado

    //Inicializando atributos para leitura da porta serial
    QString m_sensorValue;
    QByteArray serialData;
    QString serialBuffer;

    bool segueAnterior;
};

#endif // SCANNERCV_H