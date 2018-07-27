#include "Monitor.h"
#include "ui_Monitor.h"

Monitor::Monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);

    listLayout = new QVBoxLayout(ui->lwHosts);
    listLayout->setSpacing(6);
    listLayout->setMargin(0);
    listLayout->setAlignment(Qt::AlignTop);
    ui->lwHosts->setLayout(listLayout);

    connect(ui->btAdd, SIGNAL(clicked()), this, SLOT(addHost()));
    connect(ui->btClose, SIGNAL(clicked()), this, SLOT(close()));

    setWindowTitle(tr("%1 %2").arg(APP_NAME).arg(APP_VERSION));
}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::addHost()
{
    HostIP* host = new HostIP();

    listLayout->insertWidget(0, host);
}

void Monitor::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME, tr("Desea salir de la App?\n"), QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes)
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}
