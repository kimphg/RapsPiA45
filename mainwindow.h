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
private:
    Ui::MainWindow *ui;
    QString serialData;
    bool openSerial(const QString &port, qint32 baudRate);
};

#endif // MAINWINDOW_H
