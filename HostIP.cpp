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
    ui->lbStatus->setStyleSheet("background-color:red;");
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
        ui->lbLastRequest->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
        ui->lbStatus->setText("Activo");
        ui->lbStatus->setStyleSheet("background-color:green;");
    }
    else
    {
        ui->lbStatus->setText("No Activo");
        ui->lbStatus->setStyleSheet("background-color:red;");
    }
}

void HostIP::enabledHost(bool enabled)
{
    if(enabled)
    {
        ui->tbIP->setEnabled(false);

        timer->start();
    }
    else
    {
        ui->tbIP->setEnabled(true);

        timer->stop();
    }
}
