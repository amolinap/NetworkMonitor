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
    connect(ping, SIGNAL(emitStatus(bool,QString)), this, SLOT(pingIsOk(bool,QString)));
    connect(ui->btRemove, SIGNAL(clicked()), this, SLOT(removeHost()));
    connect(ui->btIP, SIGNAL(clicked()), this, SLOT(captureHost()));
    connect(ui->btName, SIGNAL(clicked()), this, SLOT(captureName()));
}

HostIP::~HostIP()
{
    delete ui;
}

void HostIP::enabledHost(bool enabled)
{
    if(enabled)
    {
        ui->btIP->setEnabled(false);
        ui->btName->setEnabled(false);

        ping->setIP(ui->btIP->text());
        ping->start();
    }
    else
    {
        ui->btIP->setEnabled(true);
        ui->btName->setEnabled(true);

        ping->terminate();
    }
}

void HostIP::pingIsOk(bool value, QString ip)
{
    QString time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

    if (value)
    {
        ui->lbLastRequest->setText(time);
        ui->lbStatus->setText("Activo");
        ui->lbStatus->setStyleSheet("background-color:#40FF00;border-radius: 12px;");

        emit emitLOGMessage(time + " \t " + ip + " \t [" + ui->btName->text() + "] \t Ping Ok!!!");
    }
    else
    {
        ui->lbLastError->setText(time);
        ui->lbStatus->setText("No Activo");
        ui->lbStatus->setStyleSheet("background-color:#FF0000;border-radius: 12px;");

        emit emitLOGMessage(time + " \t " + ip + " \t [" + ui->btName->text() + "] \t Ping Error!!!");
    }
}

QString HostIP::getIP()
{
    return ui->btIP->text();
}

QString HostIP::getName()
{
    return ui->btName->text();
}

int HostIP::getCheck()
{
    return ui->cxEnabled->isChecked() ? 1 : 0;
}

void HostIP::setIP(QString ip)
{
    ui->btIP->setText(ip);
}

void HostIP::setName(QString name)
{
    ui->btName->setText(name);
}

void HostIP::setCheck(int value)
{
    if(value == 1)
    {
        ui->cxEnabled->setChecked(true);
        enabledHost(true);
    }
}

void HostIP::removeHost()
{
    emit emitHost(this);
}

void HostIP::captureHost()
{
    bool ok;

    QString text = QInputDialog::getText(0, "Ingresar Información", "IP:", QLineEdit::Normal, ui->btIP->text(), &ok);

    if (ok && !text.isEmpty())
    {
        ui->btIP->setText(text);
    }
}

void HostIP::captureName()
{
    bool ok;

    QString text = QInputDialog::getText(0, "Ingresar Información", "Nombre:", QLineEdit::Normal, ui->btName->text(), &ok);

    if (ok && !text.isEmpty())
    {
        ui->btName->setText(text);
    }
}
