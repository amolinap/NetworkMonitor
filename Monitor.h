#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include "HostIP.h"

namespace Ui {
class Monitor;
}

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

private:
    Ui::Monitor *ui;
    QVBoxLayout *listLayout;

private slots:
    void addHost();
};

#endif // MONITOR_H
