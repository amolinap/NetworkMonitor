#ifndef PING_H
#define PING_H

#include <QThread>
#include <QProcess>
#include <QDebug>

class Ping : public QThread
{
    Q_OBJECT

public:
    Ping();
    ~Ping();

    void setIP(QString value);
    QString getIP();

private:
    QString ip;
    QProcess* pingProcess;
    QString nParameter;
    QString pingCount;
    QString wParameter;
    QString pingWaitTime;

protected slots:
    void run();
    void checkHostIP();

signals:
    void emitStatus(bool ping, QString ip);
};

#endif // PING_H
