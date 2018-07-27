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
