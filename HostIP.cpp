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
}

HostIP::~HostIP()
{
    delete ui;
}

void HostIP::CheckHostIP()
{
    int returnedCode = QProcess::execute("ping", QStringList() << "-c 1" << ui->tbIP->text());

    if (returnedCode == 0)
    {
        ui->lbStatus->setText("Activo");
        ui->lbStatus->setStyleSheet("background-color:green;");
    } else
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
