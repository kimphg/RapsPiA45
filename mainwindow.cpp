#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QKeyEvent>
#include <QScreen>
#include <QSerialPortInfo>
#include <QWindow>
QHash<QString, double>  tesResult;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->tabBar()->hide();
    this->showFullScreen();
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
            WriteSerial("$PC100");
            //ui->label_message->setText(portname);
            printf("\nSerial port active:");
            //fflushall();
            printf(portname.toStdString().data());
            connect(&serialPort, SIGNAL(readyRead()), this, SLOT(ProcessSerialData()));
            WriteSerial("$PC100");

        }
    }
    tesResult.insert("$TBBA2Adm",27.0); tesResult.insert("$TBBA2Ass",1.3);
    tesResult.insert("$TBBA2Bdm",27.0); tesResult.insert("$TBBA2Bss",1.3);
    tesResult.insert("$TBBA2Cdm",0.00); tesResult.insert("$TBBA2Css",0.6);
    tesResult.insert("$TBBA2Ddm",27.0); tesResult.insert("$TBBA2Dss",1.3);
    tesResult.insert("$TBBA2Edm",27.0); tesResult.insert("$TBBA2Ess",1.3);
    tesResult.insert("$TBBA2Fdm",27.0); tesResult.insert("$TBBA2Fss",1.3);
    tesResult.insert("$TBBA2Gdm",27.0); tesResult.insert("$TBBA2Gss",1.3);
    tesResult.insert("$TBBA2Hdm",100.0);tesResult.insert("$TBBA2Hss",82.0);
    tesResult.insert("$TBBA2Idm",27.0); tesResult.insert("$TBBA2Iss",1.3);
    tesResult.insert("$TBBA2Jdm",27.0); tesResult.insert("$TBBA2Jss",1.3);
    tesResult.insert("$TBBA2Kdm",12.6); tesResult.insert("$TBBA2Kss",0.6);
    tesResult.insert("$TBBA2kdm",-12.6); tesResult.insert("$TBBA2kss",0.6);
    tesResult.insert("$TBBA2Ldm",20.0); tesResult.insert("$TBBA2Lss",1.0);
    tesResult.insert("$TBBA2ldm",-20.0); tesResult.insert("$TBBA2lss",1.0);
    tesResult.insert("$TBBA2Mdm",20.0); tesResult.insert("$TBBA2Mss",1.0);
    tesResult.insert("$TBBA2Ndm",27.0); tesResult.insert("$TBBA2Nss",1.3);
    tesResult.insert("$TBBA2Odm",27.0);tesResult.insert("$TBBA2Oss",1.3);

    tesResult.insert("$TBML2Adm",0.0); tesResult.insert("$TBML2Ass",1.0);
    tesResult.insert("$TBML2Bdm",0.0); tesResult.insert("$TBML2Bss",1.0);
    tesResult.insert("$TBML2Cdm",0.0); tesResult.insert("$TBML2Css",1.5);
    tesResult.insert("$TBML2Ddm",0.0); tesResult.insert("$TBML2Dss",1.5);
    tesResult.insert("$TBML2Edm",4.0); tesResult.insert("$TBML2Ess",1.0);
    tesResult.insert("$TBML2Fdm",4.0); tesResult.insert("$TBML2Fss",1.0);
    tesResult.insert("$TBML2Gdm",4.0); tesResult.insert("$TBML2Gss",1.0);
    tesResult.insert("$TBML2Hdm",4.0); tesResult.insert("$TBML2Hss",1.0);
    tesResult.insert("$TBML2Idm",0.0); tesResult.insert("$TBML2Iss",1.1);
    tesResult.insert("$TBML2Jdm",0.0); tesResult.insert("$TBML2Jss",1.1);
    startTimer(500);
}
int command = -1;
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_S)
    {

        command = 0;
    }
    else if(key == Qt::Key_1)
    {
        ui->tabWidget->setCurrentIndex(0);
    }
    else if(key == Qt::Key_2)
    {
        ui->tabWidget->setCurrentIndex(1);
    }
    else if(key == Qt::Key_3)
    {
        ui->tabWidget->setCurrentIndex(2);
    }
    else if(key== Qt::Key_4)
    {
        ui->label_bakl_1->setText("Đạt");
        ui->label_bakl_2->setText("Đạt");
        ui->label_bakl_3->setText("Đạt");
        ui->label_bakl_4->setText("Đạt");
        ui->label_bakl_5->setText("Đạt");
        ui->label_bakl_6->setText("Đạt");
        ui->label_bakl_7->setText("Đạt");
        ui->label_bakl_8->setText("Đạt");
        ui->label_bakl_9->setText("Đạt");
       ui->label_bakl_10->setText("Đạt");
       ui->label_bakl_11->setText("Đạt");
     ui->label_bakl_11_2->setText("Đạt");
       ui->label_bakl_12->setText("Đạt");
     ui->label_bakl_12_2->setText("Đạt");
       ui->label_bakl_13->setText("Đạt");
       ui->label_bakl_14->setText("Đạt");
       ui->label_bakl_15->setText("Đạt");
    }


}
void MainWindow::captureScreen(int tabIndex)
{
    captureIndex.push_back(tabIndex);

}
void MainWindow::timerEvent(QTimerEvent *event)
{
    if(command!=-1)
    {command++;
        switch (command) {
        case 1:
            ProcessData("$KTTB,100,000000,*");
            break;
        case 2:
            ProcessData("$TBBA,100,000000,*");//BA san sang
            break;
        case 3:
            break;
        case 4:
            ProcessData("$SUTB,100,,*");//tham so BA 1
            break;
        case 5:
            ProcessData("$SUTB,211,,*");//tham so BA 1
            break;
        case 6:
            //ProcessData("$TBBA,2A,+15.0,*");//tham so BA 1
            break;//
        case 7:
            ProcessData("$TBBA,2B,+26.0,*");//tham so BA 2
            break;
        case 8:
            ProcessData("$TBBA,2Z,*");//tham so BA 2
            break;
        case 9:
            ProcessData("$TBML,100,000,*");//tham so BA 2
            break;
        case 10:
            ProcessData("$TBML,2A,-20,*");//tham so BA 2
            break;
        default:
            //killTimer(event->timerId());
            command = -1;
            break;
        }
    }
    if(captureIndex.size())
    {
        int i = (captureIndex.at(captureIndex.size()-1));
        QScreen *screen = QGuiApplication::primaryScreen();
        if (const QWindow *window = windowHandle())
            screen = window->screen();
        if (!screen)
            return;

        //int oldIndex = this->ui->tabWidget->currentIndex();

        this->ui->tabWidget->setCurrentIndex(i);
        update();
        QApplication::beep();

        QPixmap originalPixmap = screen->grabWindow(0);

        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                    ui->lineEdit->text()+ui->lineEdit_2->text(),
                                    tr("Images (*.png *.jpg)"));
        originalPixmap.save(fileName);
        captureIndex.pop_back();
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
        if(ProcessData(serialData))serialData.clear();
    }
}
bool MainWindow::ProcessData(QString data)
{
    if(!data.length())return false;
    while(data.at(0)!= '$')
    {
        data.remove(0,1);
        if(!data.length())return false;
    }
    //test ok
    QStringList msgContent = data.split(',');
    if(msgContent.size()<2)return false;
    if(!msgContent.at(msgContent.size()-1).contains('*'))return false;
    ui->textBrowser->append(data);

    if(msgContent.at(0)=="$KTTB")
    {
        this->ui->tabWidget->setCurrentIndex(0);
        if(msgContent.at(1)=="100"){ui->label_message->setText("Kiểm tra thiết bị trước khi sử dụng");}
        else if (msgContent.at(1)=="2A"){ui->label_2a->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2B"){ui->label_2b->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2C"){ui->label_2c->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2D"){ui->label_2d->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2E"){ui->label_2e->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2F"){ui->label_2f->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="2G"){ui->label_2f->setText(msgContent.at(2));}
        else if (msgContent.at(1)=="300000000"){ui->label_message->setText("Kiểm tra thiết bị xong, hãy chọn chế độ BA/Máy lái");}
    }
    else if (msgContent.at(0)=="$SUTB")
    {
        //Yêu cầu chọn thiết bị, và chế độ kiểm tra: BA/Máy Lái ? tự động/ từng bước
        if(msgContent.at(1)=="100")     {ui->label_message->setText("Chọn thiết bị và chế độ kiểm tra: BA/Máy Lái ? Tự động/Từng bước?");}
        else if(msgContent.at(1)=="211"){ui->label_message->setText("Đã chọn BA");}
        else if(msgContent.at(1)=="212"){ui->label_message->setText("Đã chọn Máy lái");}
        else if(msgContent.at(1)=="221"){ui->label_message->setText("Đã đặt chế độ TỰ ĐỘNG");}
        else if(msgContent.at(1)=="222"){ui->label_message->setText("Đã đặt chế độ TỪNG BƯỚC");}


    }
    else if (msgContent.at(0)=="$TBBA")
    {
        this->ui->tabWidget->setCurrentIndex(1);
        QLabel* labelKq,*labelKl;
        tesResult.insert(msgContent.at(0)+msgContent.at(1),msgContent.at(2).toDouble());
        if(msgContent.at(1)=="100")     {ui->label_message->setText("BA sẵn sàng");return true;}

        else if(msgContent.at(1)=="2A")
        {
            labelKq=ui->label_bakq_1;
            labelKl=ui->label_bakl_1;
        }
        else if(msgContent.at(1)=="2B")
        {
            labelKq=ui->label_bakq_2;
            labelKl=ui->label_bakl_2;
        }
        else if(msgContent.at(1)=="2C")
        {
            labelKq=ui->label_bakq_3;
            labelKl=ui->label_bakl_3;
        }
        else if(msgContent.at(1)=="2D")
        {
            labelKq=ui->label_bakq_4;
            labelKl=ui->label_bakl_4;
        }
        else if(msgContent.at(1)=="2E")
        {
            labelKq=ui->label_bakq_5;
            labelKl=ui->label_bakl_5;
        }
        else if(msgContent.at(1)=="2F")
        {
            labelKq=ui->label_bakq_6;
            labelKl=ui->label_bakl_6;
        }
        else if(msgContent.at(1)=="2G")
        {
            labelKq=ui->label_bakq_7;
            labelKl=ui->label_bakl_7;
        }
        else if(msgContent.at(1)=="2H")
        {
            labelKq=ui->label_bakq_8;
            labelKl=ui->label_bakl_8;
        }
        else if(msgContent.at(1)=="2I")
        {
            labelKq=ui->label_bakq_9;
            labelKl=ui->label_bakl_9;
        }
        else if(msgContent.at(1)=="2J")
        {
            labelKq=ui->label_bakq_10;
            labelKl=ui->label_bakl_10;
        }
        else if(msgContent.at(1)=="2K")
        {
            labelKq=ui->label_bakq_11;
            labelKl=ui->label_bakl_11;
        }
        else if(msgContent.at(1)=="2k")
        {
            labelKq=ui->label_bakq_11_2;
            labelKl=ui->label_bakl_11_2;
        }
        else if(msgContent.at(1)=="2L")
        {
            labelKq=ui->label_bakq_12;;
            labelKl=ui->label_bakl_12;
        }
        else if(msgContent.at(1)=="2l")
        {
            labelKq=ui->label_bakq_12_2;
            labelKl=ui->label_bakl_12_2;
        }
        else if(msgContent.at(1)=="2M")
        {
            labelKq=ui->label_bakq_13;
            labelKl=ui->label_bakl_13;
        }
        else if(msgContent.at(1)=="2N")
        {
            labelKq=ui->label_bakq_14;
            labelKl=ui->label_bakl_14;
        }
        else if(msgContent.at(1)=="2O")
        {
            labelKq=ui->label_bakq_15;
            labelKl=ui->label_bakl_15;
        }
        else if(msgContent.at(1)=="2Z")
        {


              if((  ui->label_bakl_1->text()=="Đạt"  )&&
                 (  ui->label_bakl_2->text()=="Đạt"  )&&
                 (  ui->label_bakl_3->text()=="Đạt"  )&&
                 (  ui->label_bakl_4->text()=="Đạt"  )&&
                 (  ui->label_bakl_5->text()=="Đạt"  )&&
                 (  ui->label_bakl_6->text()=="Đạt"  )&&
                 (  ui->label_bakl_7->text()=="Đạt"  )&&
                 (  ui->label_bakl_8->text()=="Đạt"  )&&
                 (  ui->label_bakl_9->text()=="Đạt"  )&&
                 (  ui->label_bakl_10->text()=="Đạt"  )&&
                 (  ui->label_bakl_11->text()=="Đạt"  )&&
                 (  ui->label_bakl_11_2->text()=="Đạt"  )&&
                 (  ui->label_bakl_12->text()=="Đạt"  )&&
                 (  ui->label_bakl_12_2->text()=="Đạt"  )&&
                 (  ui->label_bakl_13->text()=="Đạt"  )&&
                 (  ui->label_bakl_14->text()=="Đạt"  )&&
                 (  ui->label_bakl_15->text()=="Đạt"  ))
              {

                  ui->label_bakq_all->setText("Đạt");
                  ui->label_bakq_all->setStyleSheet("QLabel { background-color : green;  }");
              }
              else
              {
                  ui->label_bakq_all->setText("Không đạt");
                  ui->label_bakq_all->setStyleSheet("QLabel { background-color : red;  }");
              }
              return true;


        }
        else
        {
            return true;
        }
        labelKq->setText(msgContent.at(2));
        QString keyname = msgContent.at(0)+msgContent.at(1);
        bool result = (abs(tesResult.value(keyname)
                           -tesResult.value(keyname+"dm"))
                       - tesResult.value(keyname+"ss"))
                <=0;
        if(result)
        {
            QByteArray feedBackData = QString(msgContent.at(0)+","
                                              +msgContent.at(1)+","
                                              +"1"+",").toLatin1();
            WriteSerial(feedBackData);
            labelKl->setText("Đạt");
            labelKl->setStyleSheet("QLabel { background-color : green;  }");
        }
        else
        {
            QByteArray feedBackData = QString(msgContent.at(0)+","
                                              +msgContent.at(1)+","
                                              +"0"+",").toLatin1();
            WriteSerial(feedBackData);
            labelKl->setText("Không đạt");
            labelKl->setStyleSheet("QLabel { background-color : red; }");
        }

    }

    else if (msgContent.at(0)=="$TBML")
    {
        this->ui->tabWidget->setCurrentIndex(2);
        QLabel* labelKq,*labelKl;
        tesResult.insert(msgContent.at(0)+msgContent.at(1),msgContent.at(2).toDouble());
        if(msgContent.at(1)=="100")     {ui->label_message->setText("Máy lái sẵn sàng ");return true;}
        else if(msgContent.at(1)=="2A"){labelKq=ui->label_mlkq_1; labelKl=ui->label_mlkl_1;}
        else if(msgContent.at(1)=="2B"){labelKq=ui->label_mlkq_2; labelKl=ui->label_mlkl_2;}
        else if(msgContent.at(1)=="2C"){labelKq=ui->label_mlkq_3; labelKl=ui->label_mlkl_3;}
        else if(msgContent.at(1)=="2D"){labelKq=ui->label_mlkq_4; labelKl=ui->label_mlkl_4;}
        else if(msgContent.at(1)=="2E"){labelKq=ui->label_mlkq_5; labelKl=ui->label_mlkl_5;}
        else if(msgContent.at(1)=="2F"){labelKq=ui->label_mlkq_6; labelKl=ui->label_mlkl_6;}
        else if(msgContent.at(1)=="2G"){labelKq=ui->label_mlkq_7; labelKl=ui->label_mlkl_7;}
        else if(msgContent.at(1)=="2H"){labelKq=ui->label_mlkq_8; labelKl=ui->label_mlkl_8;}
        else if(msgContent.at(1)=="2I"){labelKq=ui->label_mlkq_9; labelKl=ui->label_mlkl_9;}
        else if(msgContent.at(1)=="2J"){labelKq=ui->label_mlkq_10;labelKl=ui->label_mlkl_10;}
        else if(msgContent.at(1)=="2Z")
        {
          if((  ui->label_mlkl_1->text()=="Đạt"  )&&
          (  ui->label_mlkl_2->text()=="Đạt"  )&&
          (  ui->label_mlkl_3->text()=="Đạt"  )&&
          (  ui->label_mlkl_4->text()=="Đạt"  )&&
          (  ui->label_mlkl_5->text()=="Đạt"  )&&
          (  ui->label_mlkl_6->text()=="Đạt"  )&&
          (  ui->label_mlkl_7->text()=="Đạt"  )&&
          (  ui->label_mlkl_8->text()=="Đạt"  )&&
          (  ui->label_mlkl_9->text()=="Đạt"  )&&
          ( ui->label_mlkl_10->text()=="Đạt"  ))
          {

              ui->label_mlkq_all->setText("Đạt");
              ui->label_mlkq_all->setStyleSheet("QLabel { background-color : green;  }");
          }
          else
          {
              ui->label_mlkq_all->setText("Không đạt");
              ui->label_mlkq_all->setStyleSheet("QLabel { background-color : red;  }");
          }
          return true;

        }
        else return true;
        labelKq->setText(msgContent.at(2));
        QString keyname = msgContent.at(0)+msgContent.at(1);

        bool result = (abs(tesResult.value(keyname)
                           -tesResult.value(keyname+"dm"))
                       - tesResult.value(keyname+"ss"))
                <=0;
        if(result)
        {

            QByteArray feedBackData = QString(msgContent.at(0)+","
                                              +msgContent.at(1)+","
                                              +"1"+",").toLatin1();
            WriteSerial(feedBackData);
            labelKl->setText("Đạt");
            labelKl->setStyleSheet("QLabel { background-color : green;  }");
        }
        else
        {
            QByteArray feedBackData = QString(msgContent.at(0)+","
                                              +msgContent.at(1)+","
                                              +"0"+",").toLatin1();
            WriteSerial(feedBackData);
            labelKl->setText("Không đạt");
            labelKl->setStyleSheet("QLabel { background-color : red; }");
        }
    }
    else if (msgContent.at(0)=="$IDMS")
    {
        if(msgContent.at(1)=="1")
        {
            ui->label_message->setText("Hãy chọn KIỂM TRA THIẾT BỊ trước khi sử dụng");
        }
        else if(msgContent.at(1)=="2")
        {
            ui->label_message->setText("Kiểm tra Thiết bị xong!");
        }
        else if(msgContent.at(1)=="3")
        {
            ui->label_message->setText("Hãy bấm TIẾP TỤC để thiết lập chế độ kiểm tra");
        }
        else if(msgContent.at(1)=="3")
        {
            ui->label_message->setText("Hãy bấm TIẾP TỤC để thiết lập chế độ kiểm tra");
        }
        else if(msgContent.at(1)=="4")
        {
            ui->label_message->setText("Hãy chọn CHẾ ĐỘ và THIẾT BỊ cần kiểm tra");
        }
        else if(msgContent.at(1)=="5")
        {
            ui->label_message->setText("Đang chọn BA - TỰ ĐỘNG. Hãy bấm TIẾP TỤC để xác nhận");
        }
        else if(msgContent.at(1)=="6")
        {
            ui->label_message->setText("Đang chọn BA - TỪNG BƯỚC. Hãy bấm TIẾP TỤC để xác nhận");
        }
        else if(msgContent.at(1)=="7")
        {
            ui->label_message->setText("Đang chọn MÁY LÁI - TỰ ĐỘNG. Hãy bấm TIẾP TỤC để xác nhận");
        }
        else if(msgContent.at(1)=="8")
        {
            ui->label_message->setText("Đang chọn MÁY LÁI - TỪNG BƯỚC. Hãy bấm TIẾP TỤC để xác nhận");
        }
        else if(msgContent.at(1)=="9")
        {
            ui->label_message->setText("Hãy bấm BẮT ĐẦU để thực hiện đo");
        }
        else if(msgContent.at(1)=="10")
        {
            ui->label_message->setText("Hãy bấm XÓA để đo lại. TIẾP TỤC để chuyển tham số");
        }
        else if(msgContent.at(1)=="11")
        {
            ui->label_message->setText("Đã thực hiện XONG! Bấm TIẾP TỤC để đo thiết bị khác!");
        }
        else if(msgContent.at(1)=="12")ui->label_message->setText("Đã DỪNG! Bấm TIẾP TỤC để tiếp tục.");
        else if(msgContent.at(1)=="13")ui->label_message->setText("Hãy bấm BẮT ĐẦU");
        else if(msgContent.at(1)=="14")ui->label_message->setText("Hãy bấm TIẾP TỤC");
        else if(msgContent.at(1)=="15")ui->label_message->setText("Hãy bấm DỪNG");
        else if(msgContent.at(1)=="16")ui->label_message->setText("Hãy bấm XÓA");
    }

    return true;
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
void MainWindow::WriteSerial(QByteArray feedBackData)
{
    serialPort.write(feedBackData);
    ui->textBrowser->append(QString::fromLatin1(feedBackData));
}

void MainWindow::on_pushButton_2_clicked()

{

    captureScreen(ui->tabWidget->currentIndex());
}



void MainWindow::on_pushButton_4_clicked()
{
    if(ui->tabWidget->currentIndex()==2)
    {
        ui->label_mlkq_1->setText("");
    ui->label_mlkq_2->setText("");
    ui->label_mlkq_3->setText("");
    ui->label_mlkq_4->setText("");
    ui->label_mlkq_5->setText("");
    ui->label_mlkq_6->setText("");
    ui->label_mlkq_7->setText("");
    ui->label_mlkq_8->setText("");
    ui->label_mlkq_9->setText("");
    ui->label_mlkq_10->setText("");
    ui->label_mlkl_1->setText("");
    ui->label_mlkl_2->setText("");
    ui->label_mlkl_3->setText("");
    ui->label_mlkl_4->setText("");
    ui->label_mlkl_5->setText("");
    ui->label_mlkl_6->setText("");
    ui->label_mlkl_7->setText("");
    ui->label_mlkl_8->setText("");
    ui->label_mlkl_9->setText("");
    ui->label_mlkl_10->setText("");
    ui->label_mlkl_1->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_2->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_3->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_4->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_5->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_6->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_7->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_8->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_mlkl_9->setStyleSheet("QLabel { background-color : white;  }");
   ui->label_mlkl_10->setStyleSheet("QLabel { background-color : white;  }");
    }

    if(ui->tabWidget->currentIndex()==1)
    {
    ui->label_bakq_1->setText("");
    ui->label_bakq_2->setText("");
    ui->label_bakq_3->setText("");
    ui->label_bakq_4->setText("");
    ui->label_bakq_5->setText("");
    ui->label_bakq_6->setText("");
    ui->label_bakq_7->setText("");
    ui->label_bakq_8->setText("");
    ui->label_bakq_9->setText("");
    ui->label_bakq_10->setText("");
    ui->label_bakq_11->setText("");
    ui->label_bakq_11_2->setText("");
    ui->label_bakq_12_2->setText("");
    ui->label_bakq_12->setText("");
    ui->label_bakq_13->setText("");
    ui->label_bakq_14->setText("");
    ui->label_bakq_15->setText("");
    ui->label_bakl_1->setText("");
    ui->label_bakl_2->setText("");
    ui->label_bakl_3->setText("");
    ui->label_bakl_4->setText("");
    ui->label_bakl_5->setText("");
    ui->label_bakl_6->setText("");
    ui->label_bakl_7->setText("");
    ui->label_bakl_8->setText("");
    ui->label_bakl_9->setText("");
    ui->label_bakl_10->setText("");
    ui->label_bakl_11->setText("");
    ui->label_bakl_11_2->setText("");
    ui->label_bakl_12_2->setText("");
    ui->label_bakl_12->setText("");
    ui->label_bakl_13->setText("");
    ui->label_bakl_14->setText("");
    ui->label_bakl_15->setText("");
    ui->label_bakl_1->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_2->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_3->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_4->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_5->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_6->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_7->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_8->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_9->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_10->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_11->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_11_2->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_12_2->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_12->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_13->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_14->setStyleSheet("QLabel { background-color : white;  }");
    ui->label_bakl_15->setStyleSheet("QLabel { background-color : white;  }");
    }

}


// và, lệnh, bật ngắt, ô ố ồ ộ, ê ế ề ệ, a á à ạ, â ấ ậ, ơ ớ ờ ợ, o ó ọ o
