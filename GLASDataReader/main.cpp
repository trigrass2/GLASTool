#include <QCoreApplication>
#include "gla_reader.h"
#include "gla01_reader.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    gla01_reader g1r;
    if(g1r.setupDB("SS-PC","GLAS","sa","songshuang"))
    {
        g1r.test();
    }else
    {
        qDebug()<<"ERROR : DB Cannot open!";
    }
    return 0;
}
