#include <QApplication>
#include "mainwindow.h"
#include "Monitor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Monitor w;
    w.show();

    return a.exec();
}
