#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*QFile styleSheet;
    styleSheet.setFileName(":/xxx.css");
    if(styleSheet.open(QFile::ReadOnly)) {
        QString styleString = styleSheet.readAll();
        styleSheet.close();
        static_cast<QApplication*>(QApplication::instance())->setStyleSheet(styleString);
    }*/

    return a.exec();
}
