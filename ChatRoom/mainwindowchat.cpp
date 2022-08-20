#include "mainwindowchat.h"
#include "ui_mainwindowchat.h"

MainWindowChat::MainWindowChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowChat)
{
    ui->setupUi(this);
}

MainWindowChat::~MainWindowChat()
{
    delete ui;
}
