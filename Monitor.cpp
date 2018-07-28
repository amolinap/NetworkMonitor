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

    if (resBtn == QMessageBox::Yes)
    {
        event->accept();

        saveHosts();
    }
    else
    {
        event->ignore();
    }
}

void Monitor::saveHosts()
{
    qDebug()<<"QCloseEvent";

    QDomDocument xmlHosts;
    QDomElement hosts = xmlHosts.createElement("hosts");
    xmlHosts.appendChild(hosts);

    for(int i=0; i<listLayout->count();i++)
    {
        HostIP* host = (HostIP*)listLayout->itemAt(i)->widget();

        qDebug()<<host->getIP()<<" "<<host->getName();

        QDomElement hostXML = xmlHosts.createElement("host");

        QDomElement ipXML = xmlHosts.createElement("ip");
        ipXML.appendChild(xmlHosts.createTextNode(host->getIP()));

        QDomElement nameXML = xmlHosts.createElement("nombre");
        nameXML.appendChild(xmlHosts.createTextNode(host->getName()));

        hosts.appendChild(hostXML);
        hostXML.appendChild(ipXML);
        hostXML.appendChild(nameXML);
    }

    QFile file2( "../../../networkmonitor_hosts.xml" );

    if( !file2.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for writing." );

    }

    QTextStream stream2( &file2 );
    stream2 << xmlHosts.toString();

    file2.close();
}
