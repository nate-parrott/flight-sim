#ifndef REMOTECONTROLRECEIVER_H
#define REMOTECONTROLRECEIVER_H

#include <QObject>
#include "easywsclient.hpp"
#include <QElapsedTimer>
#include <QThread>

class RemoteControlReceiver : public QThread
{
    easywsclient::WebSocket *socket;
    QElapsedTimer lastMessageTime;
protected:
    void run();
public:
    RemoteControlReceiver();
    virtual ~RemoteControlReceiver();

    bool hasUpToDateData();
    float roll, pitch; // degrees

    QString connectionKey;

    void gotMessage(QString message);

};

#endif // REMOTECONTROLRECEIVER_H
