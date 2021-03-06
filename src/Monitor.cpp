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

    setWindowTitle(tr("%1 %2 | Qt v%3").arg(APP_NAME).arg(APP_VERSION).arg(QT_VERSION_STR));

    QDir directory;

    if(!directory.exists(QCoreApplication::applicationDirPath()+"/../../../LOGS"))
    {
        directory.mkdir(QCoreApplication::applicationDirPath()+"/../../../LOGS");
    }

    logName = "LOG_" + QDate::currentDate().toString("yyyyMMdd") + QTime::currentTime().toString("HHmmss") + ".txt";

    loadStyleSheet(":/Images/stylesheet.css");
    openHosts();
}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::addHost()
{
    HostIP* hostView = new HostIP(this);

    connect(hostView, SIGNAL(emitLOGMessage(QString)), this, SLOT(saveLOG(QString)));
    connect(hostView, SIGNAL(emitHost(HostIP*)), this, SLOT(removeHost(HostIP*)));

    listLayout->insertWidget(listLayout->count(), hostView);
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
    if(listLayout->count() > 0)
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

            QDomElement checkXML = xmlHosts.createElement("check");
            checkXML.appendChild(xmlHosts.createTextNode(QString::number(host->getCheck())));

            hosts.appendChild(hostXML);
            hostXML.appendChild(ipXML);
            hostXML.appendChild(nameXML);
            hostXML.appendChild(checkXML);
        }


        QFile file2(QCoreApplication::applicationDirPath()+ "/../../../networkmonitor_hosts.xml" );

        if( !file2.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            qDebug( "Failed to open file for writing." );

        }

        QTextStream stream2( &file2 );
        stream2 << xmlHosts.toString();

        file2.close();
    }
}

void Monitor::openHosts()
{
    QDomDocument xmlHosts;

    QFile file(QCoreApplication::applicationDirPath()+"/../../../networkmonitor_hosts.xml");

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug("Error al abrir archivo");
    }
    else
    {
        if(!xmlHosts.setContent(&file))
        {
            qDebug("Error al cargar archivo");
        }

        file.close();
    }

    QDomElement root = xmlHosts.firstChildElement();

    QDomNodeList hosts = root.elementsByTagName("host");

    for(int i=0; i<hosts.count(); i++)
    {
        QDomNodeList values = hosts.at(i).childNodes();

        qDebug()<<"IP "<<values.item(0).toElement().childNodes().at(0).nodeValue();
        qDebug()<<"Nombre "<<values.item(1).toElement().childNodes().at(0).nodeValue();

        HostIP* hostView = new HostIP(this);

        connect(hostView, SIGNAL(emitLOGMessage(QString)), this, SLOT(saveLOG(QString)));
        connect(hostView, SIGNAL(emitHost(HostIP*)), this, SLOT(removeHost(HostIP*)));

        hostView->setIP(values.item(0).toElement().childNodes().at(0).nodeValue());
        hostView->setName(values.item(1).toElement().childNodes().at(0).nodeValue());
        hostView->setCheck(values.item(2).toElement().childNodes().at(0).nodeValue().toInt());

        listLayout->insertWidget(i, hostView);
    }
}

void Monitor::saveLOG(QString message)
{
    QFile logFile(QCoreApplication::applicationDirPath() + "/../../../LOGS/" + logName);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream logStream(&logFile);

    logStream
            <<message<< "\t"
            << "\r\n";

    logFile.close();
}

void Monitor::removeHost(HostIP* host)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME, tr("Desea quitar de la lista:\n%1\n%2").arg(host->getIP()).arg(host->getName()), QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes)
    {
        qDebug()<<host->getIP();
        host->hide();
        listLayout->removeWidget(host);
        listLayout->update();
        qDebug()<<listLayout->count();
    }
}

void Monitor::loadStyleSheet(QString styleFileName)
{
    QFile* styleSheet = new QFile(styleFileName);
    QString style;

    if (!styleSheet->exists())
    {
        styleSheet = new QFile(":/Images/stylesheet.css");

        if(styleSheet->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            style = QString(styleSheet->readAll());
        }
    }
    else
    {
        if(styleSheet->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            style = QString(styleSheet->readAll());
        }
    }

    qApp->setStyleSheet(style);
}
