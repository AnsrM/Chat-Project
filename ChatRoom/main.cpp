#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
//设置样式表
    QFile styleSheet;
    styleSheet.setFileName(":/res/style.css");
    if(styleSheet.open(QFile::ReadOnly)) {
        QString styleString = styleSheet.readAll();
        styleSheet.close();
        static_cast<QApplication*>(QApplication::instance())->setStyleSheet(styleString);
    }
//设置样式表
    MainWindow w;
    w.show();
    return a.exec();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
