#include "mainwindowchat.h"
#include "ui_mainwindowchat.h"
#include "message.h"

extern Message *message2;
extern Message *message3;

MainWindowChat::MainWindowChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowChat)
{
    ui->setupUi(this);

    //接受user的参数，填写数据
    connect(message2,SIGNAL(sendDataToMainWindowChat(QString,QString,QString)),this,SLOT(receiveDataFromMainWindowUser(QString,QString,QString)));
    ui->text_ip->setText(myIpAddress_chat);
    ui->text_id->setText(account_chat);
    ui->text_name->setText(name_chat);

    client = new QTcpSocket(this);
    //暂时随便写的ip和端口
    QString hostAdress = "127.0.0.1";
    client->connectToHost(QHostAddress(hostAdress), 8888);
    //接受消息
    connect(client,&QTcpSocket::readyRead,this,[=]()
    {
        QByteArray recv = client->readAll();
        QString str = recv;
        ui->textBrowser_receive->append(recv);
    });

    //发送消息
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

//清空消息栏
void MainWindowChat::on_ClearButton_clicked()
{
    ui->textEdit_send->setText("");
}

void MainWindowChat::receiveDataFromMainWindowUser(QString _ip, QString _account,QString _userName)
{
    myIpAddress_chat=_ip;
    account_chat=_account;
    name_chat=_userName;
}
