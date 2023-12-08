#ifndef DIRHELP_H
#define DIRHELP_H

#include <QObject>
#include <QWidget>
#include <QString>//
#include <iostream>
#include <QVector>
#include <QVectorIterator>
#include <QtGlobal>
#include <QDebug>
#include <QDir>
#include <QFile>


class DirHelp
{
public:
    DirHelp(QString projectName);

    QString getCurrPath();
    QString getImagesPath();
    QString getTxtFilesPath();

    bool fileExists(QString filePath);
    qint8 readTextFileIntoVectorArray(QString txtFileName, QVector<qint32> *qint32Vector);

private:
    QString projectName;
    QString currPath;
    QString imagesPath;
    QString txtFilesPath;
};

#endif // DIRHELP_H
