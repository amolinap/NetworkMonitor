#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkInterface interface;

    // Then declare a QList using QHostAddress as the list type.

    // After this, you can simply use ".allAddresses()" method to get ALL the
    // network interface information, easy enough no?

    QList<QHostAddress> IpList = interface.allAddresses();

    // After that you can display the ip numbers on the console or do whatever you
    // want with them.

    for (int i = 0; i < IpList.size(); i++)
         qDebug() << "Interface " << i << ":" << IpList.at(i).toString() << endl;


    //There isn't a good cross platform way for doing this. But you can use platform specific ways :

    //On Linux you can :

    int returnedCode = QProcess::execute("ping", QStringList() << "-c 1" << ui->ipEdit->text());
    if (returnedCode == 0)
    {
        // It's active, Show Green Check
    } else
    {
        //  It's dead, Show Red Check
    }

    //On Windows it is like :

    returnedCode = QProcess::execute("ping", QStringList() << "-n 1" << ui->ipEdit->text());
    if (returnedCode == 0)
    {
        // It's active, Show Green Check
    } else
    {
        //  It's dead, Show Red Check
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
