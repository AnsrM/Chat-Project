#include "mainwindowhello.h"
#include "ui_mainwindowhello.h"

MainWindowHello::MainWindowHello(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowHello)
{
    ui->setupUi(this);
}

MainWindowHello::~MainWindowHello()
{
    delete ui;
}
