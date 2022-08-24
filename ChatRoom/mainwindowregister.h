#ifndef MAINWINDOWREGISTER_H
#define MAINWINDOWREGISTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class MainWindowRegister;
}

class MainWindowRegister : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRegister(QWidget *parent = 0);
    ~MainWindowRegister();
    QString check_id(int choice,char* name,char* password);

    //向服务器端发送信息
    void submitData();

    //向服务器端接收信息
    void receiveMsgRegister();

private:
    Ui::MainWindowRegister *ui;

signals:
    void sendDataToMainWindow(QString username, QString account,QString password);
    void closeRegister();
};

#endif // MAINWINDOWREGISTER_H
