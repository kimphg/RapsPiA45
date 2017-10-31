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
void MainWindow::timerEvent(QTimerEvent *event)
{

    ProcessData("$KTTB,100000000,");
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
    QStringList listMsg = data.split("$");
    foreach ( QString str, listMsg) {
        ui->textBrowser->append(str);
        QStringList msgContent = str.split(',');
        if(msgContent.at(0)=="KTTB")
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
        //“300000000”
//            if(str.left(4) == "KTTB")
//            {
//                if(str.size()<13)continue;
//                QString substr = str.right(9);
//                if(substr=="100000000")
//                {

//                }
//                else if(substr=="100000000")
//                {

//                }
//            }
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
