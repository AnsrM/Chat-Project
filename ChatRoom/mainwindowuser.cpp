#include "mainwindowuser.h"
#include "ui_mainwindowuser.h"
#include "message.h"
#include "QLabel"
#include "QMovie"

extern Message *message1;

MainWindowUser::MainWindowUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowUser)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("C:/Users/14769/Documents/GitHub/Chat-Project/ChatRoom/wenzi.gif");
    ui->touxiang->setMovie(movie);
    movie->start();

    connect(message1,SIGNAL(sendDataToMainWindowUser(QString,QString,QString)),this,SLOT(receiveDataFromMainWindow(QString,QString,QString)));
    ui->text_ip->setText(myIpAddress_user);
    ui->text_id->setText(account_user);
    ui->text_name->setText(name_user);
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
