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
    startTimer(1000);
}
int command = 0;
void MainWindow::timerEvent(QTimerEvent *event)
{
    command++;
    switch (command) {
    case 1:
        ProcessData("$KTTB,100000000,");
        break;
    case 2:
        ProcessData("$KTTB,100000000,");
        break;
    default:
        break;
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
        ProcessData(serialData);
    }
}
void MainWindow::ProcessData(QString data)
{
    while(data.at(0)!= '$')data.remove(0,1);
        ui->textBrowser->append(data);
        QStringList msgContent = data.split(',');
        if(msgContent.size()<3)return;
        if(msgContent.at(0)=="$KTTB")
        {
            this->ui->tabWidget->setCurrentIndex(0);
        }
        if(msgContent.at(1)=="100000000"){ui->label_message->setText("Kiểm tra thiết bị trước khi sử dụng");}
        else if (msgContent.at(1)=="2A"){ui->label_2a->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2B"){ui->label_2b->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2C"){ui->label_2c->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2D"){ui->label_2d->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2E"){ui->label_2e->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2F"){ui->label_2f->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2F"){ui->label_2f->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="300000000"){ui->label_message->setText("Kiểm tra thiết bị xong, hãy chọn chế độ BA/Máy lái");}



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
