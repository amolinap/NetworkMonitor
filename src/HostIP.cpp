#include "HostIP.h"
#include "ui_HostIP.h"

HostIP::HostIP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HostIP)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(CheckHostIP()));
    connect(ui->cxEnabled, SIGNAL(clicked(bool)), this, SLOT(enabledHost(bool)));

    //procc = new QProcess(this);
    //procc.setProcessChannelMode(QProcess::MergedChannels);
    ui->lbStatus->setText("No Activo");
    ui->lbStatus->setStyleSheet("background-color:#FF0000;border-radius: 12px;");

    ping = new Ping();
    connect(ping, SIGNAL(emitStatus(bool)), this, SLOT(pingIsOk(bool)));
}

HostIP::~HostIP()
{
    delete ui;
}

void HostIP::CheckHostIP()
{
    /*procc.execute("ping", QStringList() << "-c 1" << ui->tbIP->text());
    procc.waitForFinished(-1);

    int returnedCode  = procc.exitCode();

    if (returnedCode == 0)
    {
        ui->lbStatus->setText("Activo");
        ui->lbStatus->setStyleSheet("background-color:green;");
    } else
    {
        ui->lbStatus->setText("No Activo");
        ui->lbStatus->setStyleSheet("background-color:red;");
    }*/

    //int returnedCode = QProcess::execute("ping", QStringList() << "-c 1" << ui->tbIP->text());

    QString nParameter = "-c";
        QString pingCount = "1"; //(int)
        QString wParameter = "-W";
        QString pingWaitTime = "10"; //(ms)
        QProcess* pingProcess = new QProcess;
        int returnedCode = pingProcess->execute("ping",QStringList() << ui->tbIP->text()<<nParameter<<pingCount<<wParameter<<pingWaitTime);

    if (returnedCode == 0)
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

void HostIP::enabledHost(bool enabled)
{
    if(enabled)
    {
        ui->tbIP->setEnabled(false);
        ui->tbName->setEnabled(false);

        //timer->start();
        ping->setIP(ui->tbIP->text());
        ping->start();
    }
    else
    {
        ui->tbIP->setEnabled(true);
        ui->tbName->setEnabled(true);

        //timer->stop();
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
    ping->setName(ui->tbName->text());
}
