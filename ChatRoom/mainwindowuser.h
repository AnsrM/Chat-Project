#ifndef MAINWINDOWUSER_H
#define MAINWINDOWUSER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class MainWindowUser;
}

class MainWindowUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowUser(QWidget *parent = 0);
    ~MainWindowUser();

private:
    Ui::MainWindowUser *ui;
};

#endif // MAINWINDOWUSER_H
