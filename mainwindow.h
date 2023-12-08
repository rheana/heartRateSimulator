#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QtCore/QMetaObject>
#include <QRandomGenerator>
#include "history.h"
#include "settings.h"
#include "chart.h"
#include "dirhelp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Settings *settings;
    Session *session;
    History *h;
    Summary *summary;
    Chart *chart;

    void endSession(int, Coherence*);
    void updateHistory();

private slots:
    void on_btnSettings_clicked();

    void on_btnChallenge_clicked();

    void on_btnGoToBreath_clicked();

    void on_btnMenu_clicked();

    //void on_btnDone_clicked();

    void on_btnSelector_clicked();

    void on_btnOn_clicked();

    //void update();
    void on_btnLog_clicked();
    void updateProgress();
    void on_btnDone_clicked();
    void on_btnBreath_clicked();
    void on_btnNewSession_clicked();
    void on_back_clicked();

    void randomSummary();
    void deleteSummary();
    void viewSummary();
    void reset();
    void displaySummary(Summary*);

signals:
    void summaryReady(Summary*);

};
#endif // MAINWINDOW_H
