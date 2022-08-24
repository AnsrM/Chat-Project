#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <qpushbutton.h>
#include <mainwindowregister.h>
#include <mainwindowchat.h>
#include <mainwindowuser.h>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QSettings.h>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString userName;
    QString account;
    QString password;
    QString myIpAddress;
    QString check_id(int choice,char* name,char* password);

    MainWindowRegister* mainWindowRegister;
    MainWindowChat* mainWindowChat;
    MainWindowUser* mainWindowUser;

    //打开注册页面
    void openMainWindowRegister();

    //关闭注册页面
    void closeMainWindowRegister();

    //根据服务器端信息判断登陆成功或者失败
    void receiveMsgLogin();

    //获取本地ip地址
    QString read_ip_address();

    //点击登录
    void login();

    //保存账号密码
    void saveInfo(QString _account, QString _password);

    //读取账号密码
    void readInfo();

    //更改样式
    void changeStyle();

private:
    Ui::MainWindow *ui;
private slots:
    void receiveDataFromRegister(QString _username, QString _account,QString _password);
    void openChat();
    void closeWindowUser();
    void closeWindowChat();
};

#endif // MAINWINDOW_H
