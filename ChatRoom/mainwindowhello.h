#ifndef MAINWINDOWHELLO_H
#define MAINWINDOWHELLO_H

#include <QMainWindow>

namespace Ui {
class MainWindowHello;
}

class MainWindowHello : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowHello(QWidget *parent = 0);
    ~MainWindowHello();

    void gotoLogin();
    void gotoRegister();

private:
    Ui::MainWindowHello *ui;
};

#endif // MAINWINDOWHELLO_H
