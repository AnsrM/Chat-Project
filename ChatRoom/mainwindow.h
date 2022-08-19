#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <mainwindowregister.h>

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
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
