#ifndef MAINWINDOWCHAT_H
#define MAINWINDOWCHAT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>

namespace Ui {
class MainWindowChat;
}

class MainWindowChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowChat(QWidget *parent = 0);
    ~MainWindowChat();

    QString myIpAddress_chat;
    QString account_chat;
    QString name_chat;

    void receiveMsg();

    void returnUser();

signals:
    void closeWindowChat();

private slots:
    void on_ClearButton_clicked();
    void receiveDataFromMainWindowUser(QString _ip, QString _account,QString _userName);
    void timerUpdata(void);
    void changeIcon_Chat(int m);

private:
    Ui::MainWindowChat *ui;
};

#endif // MAINWINDOWCHAT_H
