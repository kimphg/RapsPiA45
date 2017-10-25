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
    QString portname = (portList.last()).portName();
    if(!openSerial(portname,9600))
    {
        printf("\nSerial port fail");
    }
    else
    {
        printf("\nSerial port active:");
        printf(portname.toStdString().data());
        connect(&serialPort, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
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
