#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <mainwindowregister.h>
#include <QTcpSocket>
#include <QHostAddress>

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

    //打开注册页面
    void openMainWindowRegister();

    //点击登录，返回0代表登陆失败
    int login();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
