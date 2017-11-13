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
    void keyPressEvent(QKeyEvent *event);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QString serialData;
    QList<int> captureIndex;
    bool openSerial(const QString &port, qint32 baudRate);
    bool ProcessData(QString data);
    void captureScreen(int tabIndex);
    void WriteSerial(QByteArray feedBackData);
};

#endif // MAINWINDOW_H
