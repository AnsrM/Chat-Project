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

    QString account_user;
    QString myIpAddress_user;
    QString name_user;
    QString accountFriend;
    QTcpSocket* client;

private:
    Ui::MainWindowUser *ui;

private slots:
    void receiveDataFromMainWindow(QString _ip, QString _account,QString _userName);
};

#endif // MAINWINDOWUSER_H
