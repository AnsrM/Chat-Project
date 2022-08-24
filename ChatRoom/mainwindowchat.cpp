#include "mainwindowchat.h"
#include "ui_mainwindowchat.h"
#include "message.h"
<<<<<<< Updated upstream
=======
#include <ctime>
#include <cstring>
>>>>>>> Stashed changes

extern Message *message2;
extern Message *message3;
extern QTcpSocket* client;

MainWindowChat::MainWindowChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowChat)
{
    ui->setupUi(this);

    setWindowTitle("Chatting");

    //接受user的参数，填写数据
    connect(message2,SIGNAL(sendDataToMainWindowChat(QString,QString,QString)),this,SLOT(receiveDataFromMainWindowUser(QString,QString,QString)));

    //接受消息
    connect(client, &QTcpSocket::readyRead, this, &MainWindowChat::receiveMsg);

    //发送消息
    connect(ui->SendButton,&QPushButton::clicked,this,[=]()
    {
        QString str = ui->textEdit_send->toPlainText();
        if(str.isEmpty())
        {
            QMessageBox::critical(this, "警告", "发送消息为空！", QMessageBox::Ok);
        }
<<<<<<< Updated upstream
        client->write(str.toLocal8Bit());

        ui->textEdit_receive->append("<font color=\"#0000FF\">我: </font>" + str + '\n');
        ui->textEdit_send->setText("");
    });

    connect(ui->pushButtonReturn, &QPushButton::clicked, this, &MainWindowChat::returnUser);
=======
        else if(str.length()>128){
            QMessageBox::critical(this, "警告", "超出输入上限（128）！", QMessageBox::Ok);
        }
        else{
            //打包
            char get_send_buffer[170];
            char time_buf[26];//时间
            time_t t;
            time(&t);
            memset(get_send_buffer,0,sizeof(get_send_buffer));

            //类型转换
            QByteArray nms,ids,cns;
//            qDebug()<<name_chat;
//            qDebug()<<account_chat;
//            qDebug()<<str;
            nms.append(name_chat);
            ids.append(account_chat);
            cns.append(str);
            //发送者
            memcpy(get_send_buffer+0,ids.data(),4);
            memcpy(get_send_buffer+4,nms.data(),4);
            //发送内容
            memcpy(get_send_buffer+8,cns.data(),cns.length());
            //发送时间
            memcpy(get_send_buffer+136,ctime_r(&t,time_buf),26);
            for(int i=0;i<162;i++){
              if(get_send_buffer[i] == '\0')
                  get_send_buffer[i] = '/';
            }
            QString msg(get_send_buffer);
            client->write(msg.toLocal8Bit());


            ui->textEdit_receive->append("<font color=\"#0000FF\">我: </font>" + str + '\n');
            ui->textEdit_send->setText("");

        }
    });

    connect(ui->pushButtonReturn, &QPushButton::clicked, this, &MainWindowChat::returnUser);

    //显示时间
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdata()));
    timer->start(1000);
>>>>>>> Stashed changes
}

MainWindowChat::~MainWindowChat()
{
    delete ui;
}

//清空消息栏
void MainWindowChat::on_ClearButton_clicked()
{
    ui->textEdit_send->setText("");
}

void MainWindowChat::receiveDataFromMainWindowUser(QString _ip, QString _account,QString _userName)
{
    myIpAddress_chat=_ip;
    account_chat=_account;
    name_chat=_userName;
    ui->text_ip->setText(myIpAddress_chat);
    ui->text_id->setText(account_chat);
    ui->text_name->setText(name_chat);
}

void MainWindowChat::receiveMsg()
{
    QString str(client->readAll());
<<<<<<< Updated upstream
    ui->textEdit_receive->append(str+"\n");
=======
    qDebug()<<str;
    //解包
    char* recv_buffer = str.toLatin1().data();//162
    char writer[4];
    char time_m[26];
    char cnt[128];

    for(int i=0;i<162;i++){
        if(recv_buffer[i] == '/'){
            recv_buffer[i] = '\0';
        }
    }
    memcpy(writer,recv_buffer+4,4);
    memcpy(cnt,recv_buffer+8,128);
    memcpy(time_m,recv_buffer+136,26);

    QString W = QString(writer);
    QString C = QString(cnt);
    QString T = QString(time_m);

    qDebug()<<W;
    qDebug()<<C;
    qDebug()<<T;

    ui->textEdit_receive->append(W+":"+C+"\n"+T);
>>>>>>> Stashed changes
}

void MainWindowChat::returnUser()
{
    emit closeWindowChat();
    disconnect(client, &QTcpSocket::readyRead, this, &MainWindowChat::receiveMsg);
}
<<<<<<< Updated upstream
=======

void MainWindowChat::timerUpdata()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->labelTime->setText(str);
}
>>>>>>> Stashed changes
