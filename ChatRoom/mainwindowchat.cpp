#include "mainwindowchat.h"
#include "ui_mainwindowchat.h"
#include "message.h"

extern Message *message2;
extern Message *message3;
extern QTcpSocket* client;

MainWindowChat::MainWindowChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowChat)
{
    ui->setupUi(this);

    //接受user的参数，填写数据
    connect(message2,SIGNAL(sendDataToMainWindowChat(QString,QString,QString)),this,SLOT(receiveDataFromMainWindowUser(QString,QString,QString)));

    //接受消息
    connect(client, &QTcpSocket::readyRead, this, &MainWindowChat::receiveMsg);

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

    connect(ui->pushButtonReturn, &QPushButton::clicked, this, &MainWindowChat::returnUser);
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
    ui->text_ip->setText(myIpAddress_chat);
    ui->text_id->setText(account_chat);
    ui->text_name->setText(name_chat);
}

void MainWindowChat::receiveMsg()
{
    QString str(client->readAll());
    ui->textEdit_receive->append(str+"\n");
}

void MainWindowChat::returnUser()
{
    emit closeWindowChat();
    disconnect(client, &QTcpSocket::readyRead, this, &MainWindowChat::receiveMsg);
}
