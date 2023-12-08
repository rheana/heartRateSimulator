#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>


Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    m_step(0),
    m_x(0),
    m_y(0)
{

    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    QObject::connect(&m_timer2, &QTimer::timeout, this, &Chart::handleTimeoutTimeElapsed);
    m_timer2.setInterval(1000);


    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(5);
    m_axisX->setRange(0, 10);
    m_axisX->setTitleText("Time(s)");
    m_axisY->setTickCount(5);
    m_axisY->setRange(0, 0.1);
    m_axisY->setTitleText("HRV(ms)");

    status = 0;
    mode = 1;
    timeElapsed = 0;


}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    DirHelp *dirHelp = new DirHelp("teamproject_3004");
    QString txtFilePath = dirHelp->getImagesPath();
    txtFilePath.append(QString("heart-rate1.png"));

    QPixmap pixHeart(txtFilePath);
    int wHeart = inputLED->width();
    int hHeart = inputLED->height();
    QPixmap scaledHeart = pixHeart.scaled(wHeart, hHeart, Qt::KeepAspectRatio);
    QIcon icon(scaledHeart);
    inputLED->setIcon(icon);
    inputLED->show();

    QString txtFilePath2 = dirHelp->getImagesPath();
    txtFilePath2.append(QString("heart-rate0.png"));

    QPixmap pixHeart2(txtFilePath);
    int wHeart2 = inputLED->width();
    int hHeart2 = inputLED->height();
    QPixmap scaledHeart2 = pixHeart.scaled(wHeart2, hHeart2, Qt::KeepAspectRatio);
    QIcon icon2(scaledHeart2);
    inputLED->setIcon(icon2);
    inputLED->show();

    //qDebug() << hrvMeasurementTriplet;
    //qDebug() << "timeelapsed:"<<timeElapsed;
    qint32 currInt;
    if(hrvMeasurementTriplet.size() < 3){
        if(i->hasNext()){
            currInt = i->next();
            hrvMeasurementTriplet.push_back(currInt);
            m_timer.setInterval(currInt);
            m_timer.start();
            timeElapsed += currInt;
        }
        else{
            m_timer.stop();
        }
    }
    else{
        qDebug() << "full";
        // grab the three here and get the new point to add

        qint32 a = hrvMeasurementTriplet[0];
        qint32 b = hrvMeasurementTriplet[1];
        qint32 c = hrvMeasurementTriplet[2];
        qreal bMinusASquared = qreal(b - a)*qreal(b - a);
        qreal cMinusBSquared = qreal(c - b)*qreal(c - b);
        qreal averageOf3MeasurementsAdded = qreal((bMinusASquared + cMinusBSquared)/2);
        qreal squareRootOfAverage = qSqrt(averageOf3MeasurementsAdded);
        qDebug() << "RRMSSD: " << squareRootOfAverage/1000;

        qreal x = (plotArea().width() / 10)*0.82;
        qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
        m_x += y;
        m_y = squareRootOfAverage/1000;
        qreal timeElapsedSec = timeElapsed/1000;
        qDebug() << "APPENDING: " << "[" << timeElapsedSec << "," << m_y <<"]";
        m_series->append(timeElapsedSec, m_y);
        qDebug()<<hrvMeasurementTriplet.back();
        //qreal scrollAmt = hrvMeasurementTriplet.back()/1000;
        scrolledSoFar+=x;
        qDebug() <<scrolledSoFar;
        scroll(x, 0);


        if(i->hasNext()){
            qint32 removed = hrvMeasurementTriplet.front();
            hrvMeasurementTriplet.pop_front();
            currInt = i->next();
            hrvMeasurementTriplet.push_back(currInt);
            m_timer.setInterval(currInt);
            m_timer.start();
            timeElapsed += currInt;
            qDebug() << "removed" << removed;
            qDebug() << "new three: " << hrvMeasurementTriplet;

        }
        else {
            m_timer.stop();
        }
    }
}

void Chart::handleTimeoutTimeElapsed(){
    if(m_timer2.interval() != 1000){
        m_timer2.setInterval(1000);
    }

    qint32 temp = lengthText->text().toInt();
    qDebug() << temp;
    temp +=1 ;
    lengthText->setNum(temp);

}

void Chart::printChartStatus(){
    qDebug() << "Chart Status: " << this->status;
    qDebug() << "Chart Mode: " << this->getMode();
}

void Chart::setStatus(qint8 newStatus){
    this->status = newStatus;
}

qint8 Chart::getStatus() {
    return this->status;
}

void Chart::setMode(qint8 newMode) {
    this->mode = newMode;
}

qint8 Chart::getMode(){
    return this->mode;
}

void Chart::setCurrRRIntArr(QVector<qint32> currRRIntArrReadIn){
    this->currRRIntArr =currRRIntArrReadIn;
}

QVector<qint32> Chart::getCurrRRIntArr(){
    return this->currRRIntArr;
}

void Chart::printCurrRRIntArr() {
    QVectorIterator<qint32> i(this->currRRIntArr);
    QString formattedMeasurement = QString("[");
    int counter = 0;
    while(i.hasNext()){
        qint32 thisInt = i.next();
        QString thisNumberPrinted;
        thisNumberPrinted = QString::number(thisInt, 'g', 6);

        if(counter != 0){
            formattedMeasurement.append(QString(" "));
        }

        formattedMeasurement.append(thisNumberPrinted);

        counter += 1;
        if(counter == 3){
            formattedMeasurement.append("]");
            counter = 0;
            qDebug() << qPrintable(formattedMeasurement);
            formattedMeasurement = QString("[");
        }
    }
}

void Chart::startTimer(){
    lengthText->setText("0");
    qint32 currInt;

    if(i->hasNext()){
        currInt = i->next();
        timeElapsed += currInt;
        hrvMeasurementTriplet.push_back(currInt);
        m_timer.setInterval(hrvMeasurementTriplet.front());

        m_timer2.setInterval(1000 - currInt);

        m_timer.start();
        m_timer2.start();
    }
}

void Chart::stopTimer(){
    currRRIntArr.clear();
    hrvMeasurementTriplet.clear();
    timeElapsed = 0;
    m_series->clear();
    scroll(-(scrolledSoFar),0);
    scrolledSoFar = 0;
    m_timer.stop();
}

void Chart::setLED(QPushButton *button){
    inputLED = button;
    QString txtFilePath;
    txtFilePath.append(QDir().absolutePath());
    txtFilePath.append(QString("/../"));
    txtFilePath.append(QString("project1v2"));
    txtFilePath.append(QString("/images/"));
    txtFilePath.append(QString("heart-rate0.png"));
    qDebug() << txtFilePath;

    QPixmap pixHeart(txtFilePath);
    int wHeart = inputLED->width();
    int hHeart = inputLED->height();
    QPixmap scaledHeart = pixHeart.scaled(wHeart, hHeart, Qt::KeepAspectRatio);
    QIcon icon(scaledHeart);
    inputLED->setIcon(icon);
    inputLED->show();
}

void Chart::setCohLabel(QLabel *label){
    coherenceText = label;
    coherenceText->setNum(0);
}

void Chart::setLenLabel(QLabel *label){
    lengthText = label;
    lengthText->setNum(0);
}

void Chart::setAchLabel(QLabel *label){
    achievementText = label;
    achievementText->setNum(0);
}
