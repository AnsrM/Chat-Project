#include "mainwindowuser.h"
#include "ui_mainwindowuser.h"
#include "message.h"
#include "QLabel"
#include "QMovie"

extern Message *message1;
extern QTcpSocket* client;
Message *message3 = new Message();

MainWindowUser::MainWindowUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowUser)
{
    ui->setupUi(this);

    setWindowTitle("用户界面");

    //接受主窗口的数据
    connect(message1,SIGNAL(sendDataToMainWindowUser(QString,QString,QString)),this,SLOT(receiveDataFromMainWindow(QString,QString,QString)));

    //查找好友账号
    connect(ui->FindFriendButton,&QPushButton::clicked,this,[=]()
    {
        QString accountFriend=ui->textEdit_friend->toPlainText();
        if(accountFriend.isEmpty())
        {
            QMessageBox::critical(this, "警告", "查找账号为空！", QMessageBox::Ok);
        }
        else
        {
            client->write(accountFriend.toLocal8Bit());
        }

    });

    //发送好友账号给服务器，接收数据消息
    connect(client, &QTcpSocket::readyRead, this, &MainWindowUser::receiveDataFromServer);

    //返回登录
    connect(ui->pushButtonReturn, &QPushButton::clicked, this, &MainWindowUser::returnLogin);

    //更换头像
    connect(ui->pushButton_change, &QPushButton::clicked, this, &MainWindowUser::changeIcon);

    changeIcon();
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
    ui->text_ip->setText(myIpAddress_user);
    ui->text_id->setText(account_user);
    ui->text_name->setText(name_user);
}

void MainWindowUser::receiveDataFromServer()
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
        emit message3->openMainWindowChat();
        emit message3->sendChangesToChat(changes);
        disconnect(client, &QTcpSocket::readyRead, this, &MainWindowUser::receiveDataFromServer);
        this->hide();
    }
}

void MainWindowUser::returnLogin()
{
    emit closeWindowUser();
    disconnect(client, &QTcpSocket::readyRead, this, &MainWindowUser::receiveDataFromServer);
}




void MainWindowUser::changeIcon()
{
    changes = (changes + 1) % 7;

    QImage *img=new QImage;

    switch (changes) {
    case 0:
        img->load(":/new/fengnv.JPG");
        break;
    case 1:
        img->load(":/new/foyege.JPG");
        break;
    case 2:
        img->load(":/new/lulu.JPG");
        break;
    case 3:
        img->load(":/new/maomi.JPG");
        break;
    case 4:
        img->load(":/new/wanhao.JPG");
        break;
    case 5:
        img->load(":/new/nandao.JPG");
        break;
    default:
        img->load(":/new/yasuo.JPG");
        break;
    }

    QPixmap icon = QPixmap::fromImage(*img).scaled(ui->labelIcon->size(),Qt::KeepAspectRatio);

    ui->labelIcon->setPixmap(icon);
}
