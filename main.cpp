#include "mainwindow.h"
#include "dirhelp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //testing purposes
    // testing directory helper class
    //DirHelp *dirPath = new DirHelp(QString("teamproject_3004"));
    //1 qDebug() << dirPath->currPath;
    //2 qDebug() << dirPath->imagesPath;
    //3 qDebug() << dirPath->txtFilesPath;
    //4 qDebug() << dirPath->fileExists(dirPath->getTxtFilesPath().append("rrdata1.txt"));

    /* 5 (spec. testing pass by reference read into vector array)
    QVector<qint32> vArrTest;
    dirPath->readTextFileIntoVectorArray(
                "rrdata1.txt", &vArrTest);
    QVectorIterator<qint32> vArrTestIt(vArrTest);

    while(vArrTestIt.hasNext()){
        qDebug() << vArrTestIt.next();
    }*/



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
