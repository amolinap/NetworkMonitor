#include "HostIP.h"
#include "ui_HostIP.h"

HostIP::HostIP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HostIP)
{
    ui->setupUi(this);

    connect(ui->cxEnabled, SIGNAL(clicked(bool)), this, SLOT(enabledHost(bool)));

    ui->lbStatus->setText("No Activo");
    ui->lbStatus->setStyleSheet("background-color:#FF0000;border-radius: 12px;");

    ping = new Ping();
    connect(ping, SIGNAL(emitStatus(bool)), this, SLOT(pingIsOk(bool)));
}

HostIP::~HostIP()
{
    delete ui;
}

void HostIP::enabledHost(bool enabled)
{
    if(enabled)
    {
        ui->tbIP->setEnabled(false);
        ui->tbName->setEnabled(false);

        ping->setIP(ui->tbIP->text());
        ping->start();
    }
    else
    {
        ui->tbIP->setEnabled(true);
        ui->tbName->setEnabled(true);

        ping->terminate();
    }
}

void HostIP::pingIsOk(bool value)
{
    if (value)
    {
        ui->lbLastRequest->setText(QDateTime::currentDateTime().toString("dd/MM/yyyy \n hh:mm:ss"));
        ui->lbStatus->setText("Activo");
        ui->lbStatus->setStyleSheet("background-color:#40FF00;border-radius: 12px;");
    }
    else
    {
        ui->lbStatus->setText("No Activo");
        ui->lbStatus->setStyleSheet("background-color:#FF0000;border-radius: 12px;");
    }
}

QString HostIP::getIP()
{
    return ui->tbIP->text();
}

QString HostIP::getName()
{
    return ui->tbName->text();
}

void HostIP::setIP(QString ip)
{
    ui->tbIP->setText(ip);
}

void HostIP::setName(QString name)
{
    ui->tbName->setText(name);
}
