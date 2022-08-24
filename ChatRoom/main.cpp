#include "mainwindow.h"
#include <QApplication>
#include <QSettings.h>
#include <QFile>

void setCss()
{
    QString path = "./css.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);

    int cssChoice = config -> value(QString("config/") + "css").toInt();

    QFile styleSheet;

    switch (cssChoice)
    {
    case 0:
        styleSheet.setFileName(":/xxx.css");
        break;
    case 1:
        styleSheet.setFileName(":/yyy.css");
        break;
    case 2:
        styleSheet.setFileName(":/zzz.css");
        break;
    default:
        break;
    }

    if(styleSheet.open(QFile::ReadOnly)) {
        QString styleString = styleSheet.readAll();
        styleSheet.close();
        static_cast<QApplication*>(QApplication::instance())->setStyleSheet(styleString);
    }

    qDebug() <<cssChoice;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setCss();

    MainWindow w;
    w.show();

    return a.exec();
}
