#include "mainwindowregister.h"
#include "ui_mainwindowregister.h"

extern QTcpSocket* client;

//处理登陆注册信息的字符串
MainWindowRegister::MainWindowRegister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRegister)
{
    ui->setupUi(this);

    setWindowTitle("注册");

    //将数据发送给服务器端
    connect(ui->pushButtonSubmit, &QPushButton::clicked, this, &MainWindowRegister::submitData);

    //从服务器端接收信号
    connect(client, &QTcpSocket::readyRead, this, &MainWindowRegister::receiveMsgRegister);

    connect(ui->pushButtonReturn, &QPushButton::clicked, this, &MainWindowRegister::closeRegister);
}

MainWindowRegister::~MainWindowRegister()
{
    delete ui;
}

QString MainWindowRegister::check_id(int choice,char* name,char* password){
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


void MainWindowRegister::submitData()
{
    QString userName = ui->lineEditUserName->text();
    QString password = ui->lineEditPassword->text();
    QString passwordRepeat = ui->lineEditPasswordRepeat->text();

    int sys = 0;
    if (userName.isEmpty() || password.isEmpty() || passwordRepeat.isEmpty())
    {
        sys = 1;
    }
    else if (password != passwordRepeat)
    {
        sys = 2;
    }

    //发送格式打包
    if(sys == 1){
        QMessageBox::critical(this, "警告", "请将信息输入完整！", QMessageBox::Ok);
    }
    else if(sys == 2){
        QMessageBox::critical(this, "警告", "密码输入不一致！", QMessageBox::Ok);
    }
    else if(!sys){
        QByteArray usn;
        usn.append(userName);
        QByteArray psd;
        psd.append(password);
        QString str = check_id(2,usn.data(),psd.data());
        client->write(str.toUtf8());
    }
    sys = 0;
}

void MainWindowRegister::receiveMsgRegister()
{
    int sg = 0;
    QString buf = client->readAll();
    QString tmp = "sign up";
    for(int i=0;i<7;i++){
        if(buf[i] != tmp[i]){
            sg =1;
        }
    }
    if(!sg){
        //ui->labelError_3->setText("注册成功！");
        QString ok = "ok";
        client->write(ok.toUtf8());
        QString id = client->readAll();
    }
    else{
        QMessageBox::information(this, "恭喜", "注册成功！您的账号为" + buf, QMessageBox::Ok);
        emit sendDataToMainWindow(ui->lineEditUserName->text(), buf, ui->lineEditPassword->text());
        emit closeRegister();
    }
//    QString recv(client->readAll());


//    //0: 已有相同用户名，清除用户名
//    //其他: 成功注册，返回账号
//    if (recv == '0')
//    {
//        QMessageBox::critical(this, "警告", "已有相同用户名！", QMessageBox::Ok);
//    }
//    else
//    {
//        QMessageBox::critical(this, "恭喜", "注册成功！", QMessageBox::Ok);

//        //
//    }
}
