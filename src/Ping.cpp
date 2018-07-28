#include "Ping.h"

Ping::Ping()
{
    this->ip = "127.0.0.1";
    this->name = "localhost";
}

Ping::~Ping()
{

}

void Ping::run()
{
    forever
    {
        checkHostIP();

        QThread::msleep(5000);
    }
}

void Ping::checkHostIP()
{
    QString nParameter = "-c";
    QString pingCount = "1"; //(int)
    QString wParameter = "-W";
    QString pingWaitTime = "10"; //(ms)
    QProcess* pingProcess = new QProcess;

    int returnedCode = pingProcess->execute("ping",QStringList() << ip<<nParameter<<pingCount<<wParameter<<pingWaitTime);

    if (returnedCode == 0)
    {
        qDebug()<<"Ping ok";
        emit emitStatus(true);
        /*ui->lbLastRequest->setText(QDateTime::currentDateTime().toString("dd/MM/yyyy \n hh:mm:ss"));
        ui->lbStatus->setText("Activo");
        ui->lbStatus->setStyleSheet("background-color:#40FF00;border-radius: 12px;");*/
    }
    else
    {
        qDebug()<<"Ping bad";
        emit emitStatus(false);
        /*ui->lbStatus->setText("No Activo");
        ui->lbStatus->setStyleSheet("background-color:#FF0000;border-radius: 12px;");*/
    }
}

void Ping::setIP(QString value)
{
    ip = value;
}

void Ping::setName(QString value)
{
    name = value;
}

QString Ping::getIP()
{
    return ip;
}

QString Ping::getName()
{
    return name;
}
