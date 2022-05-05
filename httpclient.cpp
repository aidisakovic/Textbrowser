#include "httpclient.h"
#include <QDebug>
#include <QCoreApplication>

HttpClient::HttpClient(QString& host,QObject *parent) : QObject(parent)
{
    m_hostname = host;
    unsigned short port = 80;
    m_socket = new QTcpSocket(this);

    // Signal ->  Slot-Verbindung
    connect(m_socket, &QTcpSocket::connected, this, &HttpClient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &HttpClient::readyRead);

    m_socket->connectToHost(m_hostname, port); // TCP Connect
    if (!m_socket->waitForConnected(5000)) {
        qDebug() << "Connect failed!";
        exit(1);
    }
}

void HttpClient::connected()
{
    // normgerechter HTTP Request zum Server

    m_socket->write("GET / HTTP/1.1\r\nHost:" + m_hostname.toUtf8() + "\r\n\r\n");
}

void HttpClient::readyRead()
{
    // HTTP-Antwort vom Server
    qDebug() << m_socket->readAll();
    m_socket->disconnectFromHost();
    QCoreApplication::quit();
}
