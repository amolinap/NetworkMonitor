/**
 *  @file    HostIP.h
 *  @author  Alejandro Molina Pulido <am.alex09@gmail.com>
 *  @date    Julio 2018
 */
#ifndef HOSTIP_H
#define HOSTIP_H

#include <QWidget>
#include <QTimer>
#include <QProcess>
#include <QDateTime>
#include <QFile>

#include "Ping.h"

namespace Ui {
class HostIP;
}

/**
 *  @brief Clase HostIP administra la vista del host monitoreado
 *
 *  @section DESCRIPTION
 *
 *  Esta clase visualiza un widget para monitorear el resultado del comando ping
 *  mostrando el estado del host en la Red.
 *
 */
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
    void loadStyleSheet(QString styleFileName);

private:
    Ui::HostIP *ui;
    Ping* ping;

protected slots:
    void enabledHost(bool enabled);
    void pingIsOk(bool value, QString ip);
    void removeHost();

signals:
    void emitLOGMessage(QString message);
    void emitHost(HostIP* host);
};

#endif // HOSTIP_H
