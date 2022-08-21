#ifndef MAINWINDOWCHAT_H
#define MAINWINDOWCHAT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

namespace Ui {
class MainWindowChat;
}

class MainWindowChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowChat(QWidget *parent = 0);
    ~MainWindowChat();

    QTcpSocket* client;

private slots:

    void on_ClearButton_clicked();

private:
    Ui::MainWindowChat *ui;
};

#endif // MAINWINDOWCHAT_H
