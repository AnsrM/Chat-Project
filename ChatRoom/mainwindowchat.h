#ifndef MAINWINDOWCHAT_H
#define MAINWINDOWCHAT_H

#include <QMainWindow>

namespace Ui {
class MainWindowChat;
}

class MainWindowChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowChat(QWidget *parent = 0);
    ~MainWindowChat();

private:
    Ui::MainWindowChat *ui;
};

#endif // MAINWINDOWCHAT_H
