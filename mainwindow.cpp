#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QTime>
#include <QMessageBox>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_tcpSocket(NULL)
{
    ui->setupUi(this);
    ui->lineEdit_status->setText("connect");
    //    connect(ui->pushButton_output,SIGNAL(clicked()),this,SLOT(slotTest()));
    flag = 0;
    //    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(slotTestCombox()));
    //    connect(ui->pushButton_save,SIGNAL(clicked()),this,SLOT(slotSaveFile()));
    //    connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(slotOpenFile()));
    //    connect(ui->pushButton_beep,SIGNAL(clicked()),this,SLOT(slotBeepTest()));
    connect(ui->pushButton_connect,SIGNAL(clicked()),this,SLOT(slotConnect()));
    connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(slotReConnect()));
    connect(ui->pushButton_send,SIGNAL(clicked()),this,SLOT(slotSendText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



//std::ostream & operator<<(std::ostream &os,const MainWindow::Test &test)
//{
//    os<<test.m_c_cha<<" ";
//    os<<test.m_d_musi<<" ";
//    os<<test.m_i_bian<<" ";
//    os<<test.m_i_temp<<" ";
//    return os;
//}
//QDebug & operator<<(QDebug &stream,const MainWindow::Test &test)
//{
//    stream<<test.m_c_cha<<" "
//    <<test.m_d_musi<<" "
//    <<test.m_i_bian<<" "
//    <<test.m_i_temp<<" ";
//    return stream;
//}
//void MainWindow::slotTest()
//{
//    Test test;
//    //std::cout<<test;
//    qDebug()<<QString()<<test;
//}
void MainWindow::slotTestCombox()
{
    //    flag--;
    //    ui->comboBox->setCurrentIndex( flag - 1);
}

void MainWindow::slotOpenFile()
{
}

void MainWindow::slotBeepTest()
{
    // sleep(1000);
    QApplication::beep();
}

void MainWindow::slotSendText()
{
        qDebug()<<"send suseeful";
        QByteArray sen = ui->lineEdit_send->text().toLocal8Bit();
        m_tcpSocket->write(sen);
}

void MainWindow::slotConnect()
{
    QString ip = ui->lineEdit_ip->text();
    int  port = ui->lineEdit_port->text().toInt();
    if(ui->lineEdit_status->text() == QString::fromLocal8Bit("连接"))
    {
        m_tcpSocket->connectToHost(ip,port);
        if(m_tcpSocket->waitForConnected())
        {
            showWarning("connect overtime");
            return;
        }
        ui->lineEdit_status->setText(tr("connect"));
        return;
    }
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
    ui->lineEdit_status->setText(tr("disconnected"));
}

void MainWindow::slotReConnect()
{
    ui->pushButton_connect->setText("connect");
    showWarning("connect is disconnection");
}

void MainWindow::slotSaveFile()
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString current_data = current_time.toString("yyyymmddhhmmss");
    qDebug()<<(current_data);
    QString filename = tr("E:\\MarkDown\\%1.txt").arg(current_data);
    QFile myfile(filename);
    if(!myfile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(NULL,"提示","无法创建文件");
        return;
    }

    else
    {
        QString t_save;
        t_save += current_data;
        t_save += (":");
        t_save += ui->lineEdit_ip->text();
        t_save += ui->lineEdit_port->text();
        QTextStream out(&myfile);
        QString str = (tr("aaaaaaaaaaa"));
        out<<t_save<<"/n";
        out<<str;
    }
}


void MainWindow::showWarning(QString errorMess)
{

    QMessageBox::warning(this,tr("warning"),errorMess,QMessageBox::Yes,QMessageBox::Yes);

}
