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
    void setName(QString value);
    QString getIP();
    QString getName();

private:
    QString ip;
    QString name;

protected slots:
    void run();
    void checkHostIP();

signals:
    void emitStatus(bool ping);
};

#endif // PING_H
