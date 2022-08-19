#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //打开注册页面
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &MainWindow::openMainWindowRegister);

    //点击登录，发送账号和密码到服务器，并且接收服务器返回的信息
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &MainWindow::login);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMainWindowRegister()
{
    mainWindowRegister = new MainWindowRegister();
    mainWindowRegister->show();
}

int MainWindow::login()
{
    QString account = ui->textEditAccount->toPlainText();
    QString password = ui->textEditPassword->toPlainText();

    if (account.isEmpty() || password.isEmpty())
    {
        ui->labelError->setText("请填写账号密码！");
    }
}
