#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo port, portList) {
        printf("\nport:");
        printf((char*)port.portName().toStdString().data());

    }
    if(portList.size())
    {
        QString portname = (portList.last()).portName();
        if(!openSerial(portname,9600))
        {
            printf("\nSerial port fail");
        }
        else
        {
            serialPort.write("$PC100");
            printf("\nSerial port active:");
            printf(portname.toStdString().data());
            connect(&serialPort, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
            serialPort.write("$PC100");

        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ProcessSerialData()
{
    if(serialPort.isOpen())
    {
        serialData.append(serialPort.readAll());
        QStringList listMsg = serialData.split("$");
        foreach ( QString str, listMsg) {
            if(str.left(4) == "KTTB")
            {
                if(str.size()<13)continue;
                QString substr = str.right(9);
                if(substr=="100000000")
                {

                }
                else if(substr=="100000000")
                {
                    1. Nguồn +5V
                    2. nguồn +12.6V
                    3. Nguồn + 20V
                    4. Nguồn +27V

                    5. NGuồn : - 12.6V
                    6. Nguồn  : - 20V
                }
            }
        }
    }
}
bool MainWindow::openSerial(const QString &port, qint32 baudRate)
{
    serialPort.setBaudRate(baudRate);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
    serialPort.setPortName(port);

    return serialPort.open(QIODevice::ReadWrite);
}
