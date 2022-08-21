#include "mainwindowuser.h"
#include "ui_mainwindowuser.h"
#include "message.h"
#include "QLabel"
#include "QMovie"

extern Message *message1;
Message *message2;
Message *message3;

MainWindowUser::MainWindowUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowUser)
{
    ui->setupUi(this);

    //gif动图
    QMovie *movie = new QMovie("C:/Users/14769/Documents/GitHub/Chat-Project/ChatRoom/wenzi.gif");
    ui->touxiang->setMovie(movie);
    movie->start();

    client = new QTcpSocket(this);
    //暂时随便写的ip和端口
    QString hostAdress = "127.0.0.1";
    client->connectToHost(QHostAddress(hostAdress), 8888);

    //接受服务器的数据
    connect(message1,SIGNAL(sendDataToMainWindowUser(QString,QString,QString)),this,SLOT(receiveDataFromMainWindow(QString,QString,QString)));
    ui->text_ip->setText(myIpAddress_user);
    ui->text_id->setText(account_user);
    ui->text_name->setText(name_user);

    //查找好友账号
    connect(ui->FindFriendButton,&QPushButton::clicked,this,[=]()
    {
        emit message2->sendDataToMainWindowChat(myIpAddress_user,account_user,name_user);
        QString accountFriend=ui->textEdit_friend->toPlainText();
        if(accountFriend.isEmpty())
        {
            QMessageBox::critical(this, "警告", "查找账号为空！", QMessageBox::Ok);
        }
        client->write(accountFriend.toLocal8Bit());
    });

    //发送好友账号给服务器，接收数据消息
    connect(client, &QTcpSocket::readyRead, this,[=]()
    {
        QString recv(client->readAll());
        //0:未找到该用户，请重新输入
        //其他：跳转到chat页面和用户聊天
        if(recv == '0')
        {
            QMessageBox::critical(this, "警告", "未找到该用户！", QMessageBox::Ok);
            ui->textEdit_friend->setText("");
        }
        else
        {
            this->hide();
            emit message3->openMainWindowChat();
        }
    });

}

MainWindowUser::~MainWindowUser()
{
    delete ui;
}

void MainWindowUser::receiveDataFromMainWindow(QString _ip, QString _account,QString _userName)
{
    myIpAddress_user=_ip;
    account_user=_account;
    name_user=_userName;
}
