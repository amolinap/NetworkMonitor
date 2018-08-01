#ifndef HOSTIP_H
#define HOSTIP_H

#include <QWidget>
#include <QTimer>
#include <QProcess>
#include <QDateTime>

#include "Ping.h"

namespace Ui {
class HostIP;
}

class HostIP : public QWidget
{
    Q_OBJECT

public:
    explicit HostIP(QWidget *parent = 0);
    ~HostIP();

    QString getIP();
    QString getName();
    int getCheck();
    void setIP(QString ip);
    void setName(QString name);
    void setCheck(int value);

private:
    Ui::HostIP *ui;
    Ping* ping;

private slots:
    void enabledHost(bool enabled);
    void pingIsOk(bool value, QString ip);

signals:
    void emitLOGMessage(QString message);
};

#endif // HOSTIP_H
