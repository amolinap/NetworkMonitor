#include "Ping.h"

Ping::Ping()
{
    this->ip = "127.0.0.1";
    pingProcess = new QProcess;

    nParameter = "-c";
    pingCount = "1";
    wParameter = "-W";
    pingWaitTime = "10";//(ms)
}

Ping::~Ping()
{

}

void Ping::run()
{
    forever
    {
        QThread::msleep(5000);

        checkHostIP();

        QThread::msleep(5000);
    }
}

void Ping::checkHostIP()
{
    int returnedCode = pingProcess->execute("ping", QStringList() << ip << nParameter << pingCount << wParameter << pingWaitTime);

    if (returnedCode == 0)
    {
        emit emitStatus(true, ip);
    }
    else
    {
        emit emitStatus(false, ip);
    }
}

void Ping::setIP(QString value)
{
    ip = value;
}

QString Ping::getIP()
{
    return ip;
}
