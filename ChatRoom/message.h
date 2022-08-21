#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include <QStringList>
class Message: public QObject
{
    Q_OBJECT
public:
    Message(){};
signals:
    void sendDataToMainWindowUser(QString myip,QString account,QString userName);
    void sendDataToMainWindowChat(QString myip,QString account,QString userName);
    void openMainWindowChat();
};

#endif // MESSAGE_H
