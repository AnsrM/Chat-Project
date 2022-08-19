#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <mainwindowregister.h>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MainWindowRegister* mainWindowRegister;
    QTcpSocket* client;

    //打开注册页面
    void openMainWindowRegister();

    //根据服务器端信息判断登陆成功或者失败
    void receiveMsgLogin();

    //点击登录
    void login();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
