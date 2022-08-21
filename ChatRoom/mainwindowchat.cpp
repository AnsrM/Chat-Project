#include "mainwindowchat.h"
#include "ui_mainwindowchat.h"

MainWindowChat::MainWindowChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowChat)
{
    ui->setupUi(this);
    client = new QTcpSocket(this);
    //暂时随便写的ip和端口
    QString hostAdress = "127.0.0.1";
    client->connectToHost(QHostAddress(hostAdress), 8888);
    connect(client,&QTcpSocket::readyRead,this,[=]()
    {
        QByteArray recv = client->readAll();
        QString str = recv;
        ui->textBrowser_receive->append(recv);
    });

    connect(ui->SendButton,&QPushButton::clicked,this,[=]()
    {
        QString str = ui->textEdit_send->toPlainText();
        if(str.isEmpty())
        {
            QMessageBox::critical(this, "警告", "发送消息为空！", QMessageBox::Ok);
        }
        client->write(str.toLocal8Bit());
    });

}

MainWindowChat::~MainWindowChat()
{
    delete ui;
}


void MainWindowChat::on_ClearButton_clicked()
{
    ui->textEdit_send->setText("");
}
