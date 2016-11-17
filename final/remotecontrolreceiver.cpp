#include "remotecontrolreceiver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "view.h"

void handleMessage(const std::string & message)
{
    //qDebug() << "Received:" << message.c_str();
    mainView()->game.remoteControlReceiver->gotMessage(QString(message.c_str()));
}
RemoteControlReceiver::RemoteControlReceiver() : QThread()
{
}
RemoteControlReceiver::~RemoteControlReceiver() {
    if (socket) delete socket;
}
void RemoteControlReceiver::run() {
    qDebug() << "Starting";
    socket = easywsclient::WebSocket::from_url(std::string("ws://steering.herokuapp.com/"));
    //socket = easywsclient::WebSocket::from_url(std::string("ws://localhost:5017/"));
    if (!socket) {
        qDebug() << "Failed to connect";
        return;
    }
    socket->send("{\"type\": \"subscribe\"}");
    while (socket->getReadyState() != easywsclient::WebSocket::CLOSED) {
        socket->poll();
        socket->dispatch(handleMessage);
    }
}
void RemoteControlReceiver::gotMessage(QString message) {
    //qDebug() << message;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        if (obj.value(QString("type")).isString()) {
            QString type = obj.value(QString("type")).toString();
            if (type == QString("subscribed")) {
                connectionKey = obj[QString("key")].toString();
            } else if (type == QString("data")) {
                QJsonObject motion = obj.value(QString("data")).toObject();
                roll = motion.value(QString("roll")).toDouble();
                pitch = motion.value(QString("pitch")).toDouble();
                lastMessageTime.restart();

            }
        }
    }
}

bool RemoteControlReceiver::hasUpToDateData() {
    return lastMessageTime.isValid() && lastMessageTime.elapsed() < 0.5 * 1000;
}
