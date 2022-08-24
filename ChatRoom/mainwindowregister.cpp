#include "mainwindowregister.h"
#include "ui_mainwindowregister.h"

MainWindowRegister::MainWindowRegister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRegister)
{
    ui->setupUi(this);

    ui->lineEditPassword1->setEchoMode(QLineEdit::Password);
    ui->lineEditPassword2->setEchoMode(QLineEdit::Password);

    ui->pushButtonSubmit->setIcon(QIcon(":/new/prefix1/registerIconW.png"));
    ui->pushButtonSubmit->setIconSize(QSize(40,40));
    ui->pushButtonBackToLogin->setIcon(QIcon(":/new/prefix1/backIconW.png"));
    ui->pushButtonBackToLogin->setIconSize(QSize(40,40));

    client = new QTcpSocket(this);
    //暂时随便写的ip和端口
    QString hostAdress = "192.168.1.106";
    client->connectToHost(QHostAddress(hostAdress), 8000);

    //将数据发送给服务器端
    connect(ui->pushButtonSubmit, &QPushButton::clicked, this, &MainWindowRegister::submitData);

    //从服务器端接收信号
    connect(client, &QTcpSocket::readyRead, this, &MainWindowRegister::receiveMsgRegister);

    //返回登录页面
    connect(ui->pushButtonBackToLogin, &QPushButton::clicked, this, &MainWindowRegister::BackToLogin);
}

MainWindowRegister::~MainWindowRegister()
{
    delete ui;
}

void MainWindowRegister::BackToLogin()
{
    emit closeRegister();
}


void MainWindowRegister::submitData()
{
    QString userName = ui->lineEditUserName->text();
    QString password = ui->lineEditPassword1->text();
    QString passwordRepeat = ui->lineEditPassword2->text();
//    QString userName = ui->textEditUserName->toPlainText();
//    QString password = ui->textEditPassword1->toPlainText();
//    QString passwordRepeat = ui->textEditPassword2->toPlainText();
   
    int sys = 0;
    if (userName.isEmpty() || password.isEmpty() || passwordRepeat.isEmpty())
    {
        ui->labelError_3->setText("请输入用户名与密码！");
        sys = 1;
    }
    else if (password != passwordRepeat)
    {
        ui->labelError_3->setText("两次密码输入不一致！");
        sys = 1;
    }

    //发送格式：用户名|密码
    if(!sys){
        QString str = userName + "|" + password;
        client->write(str.toUtf8());
        sys = 0;
    }
}

void MainWindowRegister::receiveMsgRegister()
{
    QString recv(client->readAll());

    //0: 已有相同用户名，清除用户名
    //其他: 成功注册，返回账号
    if (recv == '0')
    {
        QMessageBox::critical(this, "警告", "已有相同用户名！", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this, "恭喜", "注册成功！", QMessageBox::Ok);
//        emit sendDataToMainWindow(ui->textEditUserName->toPlainText(), recv, ui->textEditPassword1->toPlainText());
        emit sendDataToMainWindow(ui->lineEditUserName->text(), recv, ui->lineEditPassword1->text());
        emit closeRegister();
    }
}
