#ifndef HOSTIP_H
#define HOSTIP_H

#include <QWidget>
#include <QTimer>
#include <QProcess>
#include <QDateTime>

namespace Ui {
class HostIP;
}

class HostIP : public QWidget
{
    Q_OBJECT

public:
    explicit HostIP(QWidget *parent = 0);
    ~HostIP();

private:
    Ui::HostIP *ui;
    QTimer *timer;
    //QProcess procc;

private slots:
    void CheckHostIP();
    void enabledHost(bool enabled);
};

#endif // HOSTIP_H
