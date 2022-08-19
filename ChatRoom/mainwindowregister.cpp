#include "mainwindowregister.h"
#include "ui_mainwindowregister.h"

MainWindowRegister::MainWindowRegister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRegister)
{
    ui->setupUi(this);
}

MainWindowRegister::~MainWindowRegister()
{
    delete ui;
}
