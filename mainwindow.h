#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QDebug>
#include <QtCharts>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

//    QTcpServer * m_tcpserver;
    QTcpSocket * m_tcpSocket;
    int flag;

private:
    void showWarning(QString errorMess);

private slots:
//    void slotTest();
    void slotTestCombox();
    void slotSaveFile();
    void slotOpenFile();
    void slotBeepTest();
    void slotSendText();
    void slotConnect();
    void slotReConnect();
};

struct compilTest
{
    unsigned short bitlen;
    unsigned char recvsed;
};

#endif // MAINWINDOW_H
