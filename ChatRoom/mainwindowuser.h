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
    int changes=0;

    void returnLogin();

    void changeIcon();

private:
    Ui::MainWindowUser *ui;

signals:
    void closeWindowUser();

public slots:
    void receiveDataFromMainWindow(QString _ip, QString _account,QString _userName);
    void receiveDataFromServer();
private slots:
    void on_pushButton_change_clicked();
};

#endif // MAINWINDOWUSER_H
