#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QVector>
#include <QtGlobal>
#include <QDebug>
#include <QDir>
#include <QtCore/QtMath>
#include <QVectorIterator>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include <QLabel>
#include "dirhelp.h"


QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~Chart();

    QVectorIterator<qint32> *i;

    void printChartStatus();
    void printCurrRRIntArr();

    void setStatus(qint8);
    qint8 getStatus();
    void setMode(qint8);
    qint8 getMode();
    void setCurrRRIntArr(QVector<qint32>);
    QVector<qint32> getCurrRRIntArr();
    void startTimer();
    void stopTimer();
    void setLED(QPushButton *button);
    void setCohLabel(QLabel *label);
    void setLenLabel(QLabel *label);
    void setAchLabel(QLabel *label);


public slots:
    void handleTimeout();
    void handleTimeoutTimeElapsed();

private:
    qint8 status;
    qint8 mode;
    QVector<qint32> currRRIntArr;
    QVector<qint32> hrvMeasurementTriplet;
    qreal timeElapsed;
    qreal scrolledSoFar;
    QPushButton *inputLED;

    QTimer m_timer;
    QTimer m_timer2;
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal m_step;
    qreal m_x;
    qreal m_y;

    QLabel *coherenceText;
    QLabel *lengthText;
    QLabel *achievementText;
};
//![1]

#endif /* CHART_H */
