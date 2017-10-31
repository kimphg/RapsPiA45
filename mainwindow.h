#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSerialPort serialPort;
private slots:
    void ProcessSerialData();
    void timerEvent(QTimerEvent *event);
private:
    Ui::MainWindow *ui;
    QString serialData;
    bool openSerial(const QString &port, qint32 baudRate);
    void ProcessData(QString data);
};

#endif // MAINWINDOW_H
