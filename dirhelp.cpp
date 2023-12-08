#include "dirhelp.h"

DirHelp::DirHelp(QString newProjectName)
{
    projectName = newProjectName;

    QString temp1 = QDir().absolutePath();
    temp1.append("/../");
    temp1.append(projectName);
    temp1.append("/");

    QString temp2 = temp1; // for images folder path
    temp2.append("images/");

    QString temp3 = temp1; // for txtFiles folder path
    temp3.append("txtfiles/");

    currPath = temp1;
    imagesPath = temp2;
    txtFilesPath = temp3;
}

QString DirHelp::getCurrPath(){
    return currPath;
}

QString DirHelp::getImagesPath(){
    return imagesPath;
}

QString DirHelp::getTxtFilesPath(){
    return txtFilesPath;
}

bool DirHelp::fileExists(QString filePath){
    QFileInfo inputFilePath(filePath);
    if(inputFilePath.exists() && inputFilePath.isFile()){
        return true;
    }
    else{
        return false;
    }
}

qint8 DirHelp::readTextFileIntoVectorArray(QString txtFileName, QVector<qint32> *qint32Vector){
    QString temp = txtFilesPath;
    temp.append(txtFileName);

    QFile inputFilePath(temp);
    inputFilePath.open(QIODevice::ReadOnly);
    if(!inputFilePath.isOpen()){
        qDebug() << temp;
        return -1;
    }

    QTextStream stream(&inputFilePath);
    for(QString line = stream.readLine();// then read in chart.cpp
        !line.isNull();
        line = stream.readLine()){
        qDebug() << line;
;        qint32Vector->push_back(qint32(line.toInt()));
        };

    return 0;
}

