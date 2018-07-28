#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>

#include "HostIP.h"

#define APP_NAME "Network Monitor"
#define APP_VERSION "1.0"
#define APP_BUILT_ON "JULIO 2018"

namespace Ui {
class Monitor;
}

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

    void closeEvent(QCloseEvent *event);

private:
    Ui::Monitor *ui;
    QVBoxLayout *listLayout;

private slots:
    void addHost();
    void saveHosts();
};

#endif // MONITOR_H
