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
    void setIP(QString ip);
    void setName(QString name);

private:
    Ui::HostIP *ui;
    Ping* ping;

private slots:
    void enabledHost(bool enabled);
    void pingIsOk(bool value);
};

#endif // HOSTIP_H
