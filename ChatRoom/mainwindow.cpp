#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message.h"
#include <cstring>

Message *message1 = new Message();
Message *message2 = new Message();
extern Message *message3;
QTcpSocket* client;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ChatRoom");

    client = new QTcpSocket(this);
<<<<<<< Updated upstream
    //暂时随便写的ip和端口
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
    QString hostAdress = read_ip_address();
    client->connectToHost(QHostAddress(hostAdress), 8888);
=======
    QString hostAdress = "192.168.1.106";
    qDebug()<<"your:"<<hostAdress;
    client->connectToHost(QHostAddress(hostAdress), 50000);
>>>>>>> Stashed changes

    //打开注册页面
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &MainWindow::openMainWindowRegister);

    //点击登录，发送账号和密码到服务器，并且接收服务器返回的信息
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &MainWindow::login);

    //接收服务器端信号
    connect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);

    //接受user发出的信号，打开chat页面
    connect(message3,SIGNAL(openMainWindowChat()),this,SLOT(openChat()));
<<<<<<< Updated upstream
}
=======

    //限制输入
    QRegExp rxId("^[0-9]+$");
    ui->lineEditId->setValidator(new QRegExpValidator(rxId));

    QRegExp rxPassword("^[A-Za-z0-9]+$");
    ui->lineEditPassword->setValidator(new QRegExpValidator(rxPassword));
>>>>>>> Stashed changes

    //读取账号密码
    readInfo();
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

//处理登陆注册信息的字符串
QString MainWindow::check_id(int choice,char* name,char* password){
    char ID_info[17];//存储帐号信息以及登录/注册选择
    int i;

    memset(ID_info,0,17);
    //登录，携带ID 和密码
    if(1 == choice){
      ID_info[0]='1';
      memcpy(ID_info+1,name,4);
      memcpy(ID_info+9,password,8);
    }

    //注册，携带昵称和密码
    else {
      ID_info[0]='2';
      memcpy(ID_info+5,name,4);
      memcpy(ID_info+9,password,8);
    }

    //发送帐号信息给服务器端进行验证
    for(i=0;i<16;i++){
      if(ID_info[i] == '\0'){
          ID_info[i] = '/';
      }
    }
    ID_info[i] = '\0';
    QString id_info = ID_info;
    return id_info;
}

void MainWindow::login()
{

    account = ui->lineEditId->text();

    password = ui->lineEditPassword->text();

    //
    if (account.isEmpty())
    {
        QMessageBox::critical(this, "警告", "请填写账号！", QMessageBox::Ok);
        return;
    }
    else if (password.isEmpty())
    {
        QMessageBox::critical(this, "警告", "请填写密码！", QMessageBox::Ok);
        return;
    }
    else if (account.size() > 4)
    {
        QMessageBox::critical(this, "警告", "账号不能超过4位数！", QMessageBox::Ok);
        return;
    }
    else if (password.size() > 8)
    {
        QMessageBox::critical(this, "警告", "密码不能超过8位数！", QMessageBox::Ok);
        return;
    }


    QByteArray act;
    act.append(account);
    QByteArray psd;
    psd.append(password);
    //发送格式打包
    QString str = check_id(1,act.data(),psd.data());
    client->write(str.toUtf8());
}

void MainWindow::receiveMsgLogin()
{
    int sg = 0,sg_1 = 0;
    QString buf = client->readAll();
    QString tmp = "successfully!";
    QString tmp_1 = "login failed!";
    for(int i=0;i<13;i++){
        if(buf[i] != tmp[i]){
            sg = 1;
        }
        if(buf[i] != tmp_1[i]){
            sg_1 = 1;
        }
    }
    if(!sg){
        QString ok = "ok";
        client->write(ok.toUtf8());
    }
    else if(!sg_1){
        QMessageBox::critical(this, "警告", "登录信息错误！", QMessageBox::Ok);
        ui->lineEditId->setText("");
        ui->lineEditPassword->setText("");
        login();
    }
    else{
        if(!buf.isEmpty()){
                mainWindowUser = new MainWindowUser();
                mainWindowUser->show();
                userName = buf;
                myIpAddress = read_ip_address();

<<<<<<< Updated upstream
        //接收user发出的信号，关闭user
        connect(mainWindowUser, &MainWindowUser::closeWindowUser, this, &MainWindow::closeWindowUser);

        disconnect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);

        emit message1->sendDataToMainWindowUser(myIpAddress,account,userName);
        this->hide();
=======
                //自动保存
                if (ui->checkBoxSave->isChecked())
                {
                    saveInfo(account, password);
                }
                else
                {
                    saveInfo("", "");
                }

                //接收user发出的信号，关闭user
                connect(mainWindowUser, &MainWindowUser::closeWindowUser, this, &MainWindow::closeWindowUser);

                disconnect(client, &QTcpSocket::readyRead, this, &MainWindow::receiveMsgLogin);

                emit message1->sendDataToMainWindowUser(myIpAddress,account,userName);
                this->hide();
        }
>>>>>>> Stashed changes
    }

    //0: 没有此账号，弹框，清除账号密码
    //1: 密码错误，弹框，清除密码
    //其他: 返回用户名，进入聊天界面

}

void MainWindow::receiveDataFromRegister(QString _username, QString _account, QString _password)
{
    userName = _username;
    account = _account;
    password = _password;

    ui->lineEditId->setText(account);
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
<<<<<<< Updated upstream
=======

void MainWindow::saveInfo(QString _account, QString _password)
{
    QString path = "./user.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);

    QByteArray accountB64 = _account.toLocal8Bit().toBase64();
    QString account = QString::fromLocal8Bit(accountB64);

    QByteArray passwordB64 = _password.toLocal8Bit().toBase64();
    QString password = QString::fromLocal8Bit(passwordB64);

    config -> beginGroup("config");
    config -> setValue("account", account);
    config -> setValue("password", password);
    config -> endGroup();
}

void MainWindow::readInfo()
{
    QString path = "./user.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);

    QString accountSec = config -> value(QString("config/") + "account").toString();
    QByteArray accountB64 = QByteArray::fromBase64(accountSec.toLocal8Bit());
    ui->lineEditId->setText(QString::fromLocal8Bit(accountB64));

    QString passwordSec = config -> value(QString("config/") + "password").toString();
    QByteArray passwordB64 = QByteArray::fromBase64(passwordSec.toLocal8Bit());
    ui->lineEditPassword->setText(QString::fromLocal8Bit(passwordB64));
}
>>>>>>> Stashed changes
