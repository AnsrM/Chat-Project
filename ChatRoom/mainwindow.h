#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <mainwindowregister.h>
#include <mainwindowchat.h>
#include <mainwindowuser.h>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
//#include <QSystemTrayIcon>
#include <QDir>

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
    QString currentDir;

    MainWindowRegister* mainWindowRegister;
    MainWindowChat* mainWindowChat;
    QTcpSocket* client;

    //打开注册页面
    void openMainWindowRegister();

    //关闭注册页面
    void closeMainWindowRegister();

    //根据服务器端信息判断登陆成功或者失败
    void receiveMsgLogin();

    //点击登录
    void login();

private:
    Ui::MainWindow *ui;

private slots:
    void receiveDataFromRegister(QString _username, QString _account,QString _password);
};

#endif // MAINWINDOW_H
