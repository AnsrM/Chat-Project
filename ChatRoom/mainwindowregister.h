#ifndef MAINWINDOWREGISTER_H
#define MAINWINDOWREGISTER_H

#include <QMainWindow>

namespace Ui {
class MainWindowRegister;
}

class MainWindowRegister : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRegister(QWidget *parent = 0);
    ~MainWindowRegister();

private:
    Ui::MainWindowRegister *ui;
};

#endif // MAINWINDOWREGISTER_H
