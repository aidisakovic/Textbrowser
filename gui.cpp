#include "gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(&m_client, &HttpClient::readyRead, this, &Gui::showResult);
}

void Gui::on_goButton_clicked()
{
    QString host = hostEntry->text();

    m_client.HttpClient(host);
}

void Gui::showResult(/*quint16 port, bool status*/)
{
    QString result;

    if (!m_client->waitForConnected(5000)) {
        resultBrowser->append("Connect failed!");
        exit(1);
    }

    resultBrowser->append(result);
    qDebug() << port << status;
}
