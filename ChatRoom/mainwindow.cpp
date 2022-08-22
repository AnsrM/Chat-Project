#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message.h"

Message *message1 = new Message();
Message *message2 = new Message();
extern Message *message3;
QTcpSocket* client;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new QTcpSocket(this);
    //暂时随便写的ip和端口
    QString hostAdress = "192.168.1.106";
    client->connectToHost(QHostAddress(hostAdress), 8888);

    //打开注册页面
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &MainWindow::openMainWindowRegister);

    //点击登录，发送账号和密码到服务器，并且接收服务器返回的信息
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &MainWindow::login);

    //接收服务器端信号
    connect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);

    //接受user发出的信号，打开chat页面
    connect(message3,SIGNAL(openMainWindowChat()),this,SLOT(openChat()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMainWindowRegister()
{
    mainWindowRegister = new MainWindowRegister();
    mainWindowRegister->show();
    this->hide();

    //接收注册页面的信息
    connect(mainWindowRegister, &MainWindowRegister::sendDataToMainWindow, this, &MainWindow::receiveDataFromRegister);

    //接收注册页面信号
    connect(mainWindowRegister, &MainWindowRegister::closeRegister, this, &MainWindow::closeMainWindowRegister);

    disconnect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);
}

void MainWindow::closeMainWindowRegister()
{
    mainWindowRegister->close();
    delete mainWindowRegister;

    connect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);

    this->show();
}

void MainWindow::login()
{
    account = ui->textEditAccount->toPlainText();
    password = ui->textEditPassword->toPlainText();

    if (account.isEmpty() || password.isEmpty())
    {
        ui->labelError->setText("请填写账号密码！");
        return;
    }

    //发送格式：账号|密码
    QString str = account + "|" + password;
    client->write(str.toUtf8());
}

void MainWindow::receiveMsgLogin()
{
    QString recv(client->readAll());

    //0: 没有此账号，弹框，清除账号密码
    //1: 密码错误，弹框，清除密码
    //其他: 返回用户名，进入聊天界面
    if (recv == 0)
    {
        QMessageBox::critical(this, "警告", "账号不存在！", QMessageBox::Ok);
        ui->textEditAccount->setText("");
        ui->textEditPassword->setText("");
    }
    else if (recv == 1)
    {
        QMessageBox::critical(this, "警告", "密码不正确！", QMessageBox::Ok);
        ui->textEditPassword->setText("");
    }
    else if (!recv.isEmpty())
    {
        mainWindowUser = new MainWindowUser();
        mainWindowUser->show();
        userName = recv;
        myIpAddress = read_ip_address();

        //接收user发出的信号，关闭user
        connect(mainWindowUser, &MainWindowUser::closeWindowUser, this, &MainWindow::closeWindowUser);

        disconnect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);

        emit message1->sendDataToMainWindowUser(myIpAddress,account,userName);
        this->hide();
    }

}

void MainWindow::receiveDataFromRegister(QString _username, QString _account, QString _password)
{
    userName = _username;
    account = _account;
    password = _password;

    ui->textEditAccount->setText(account);
}

QString MainWindow::read_ip_address()
{
    QString ip_address;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  ipAddressesList.at(i).toIPv4Address())
        {
            ip_address = ipAddressesList.at(i).toString();
            qDebug()<<ip_address;  //debug
            //break;
        }
    }
    if (ip_address.isEmpty())
        ip_address = QHostAddress(QHostAddress::LocalHost).toString();
    return ip_address;
}

void MainWindow::openChat()
{
    mainWindowChat = new MainWindowChat();
    mainWindowChat->show();
    connect(mainWindowChat, &MainWindowChat::closeWindowChat, this, &MainWindow::closeWindowChat);
    emit message2->sendDataToMainWindowChat(myIpAddress,account,userName);
}

void MainWindow::closeWindowUser()
{
    mainWindowUser->hide();
    this->show();
    connect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);
}

void MainWindow::closeWindowChat()
{
    mainWindowChat->hide();
    mainWindowUser->show();
    connect(client, &QTcpSocket::readyRead, mainWindowUser, &MainWindowUser::receiveDataFromServer);
}
