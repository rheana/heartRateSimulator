#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <iostream>
#include <QDebug>


using namespace std;

bool sessionStarted = false;
bool on = false;
int sec = 0;
int breathpacer = 10;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{





    ui->setupUi(this);

    ui->txtBreath->setValidator(new QIntValidator(1,30,this));
    ui->stackedWidget->setCurrentWidget(ui->page_Off);

    QPixmap pixL("/home/Rheana/images/left_arrow.png");
    QPixmap pixR("/home/Rheana/images/right_arrow.png");
    QPixmap pixU("/home/Rheana/images/up_arrow.png");
    QPixmap pixD("/home/Rheana/images/down_arrow.png");

    QPixmap pixLR("/home/Rheana/images/red_led.png");
    QPixmap pixLB("/home/Rheana/images/blue_led.png");
    QPixmap pixLG("/home/Rheana/images/green_led.png");


    int wBtnLeft = ui->btnLeft->width();
    int lBtnLeft= ui->btnLeft->height();
    int wBtnRight = ui->btnRight->width();
    int lBtnRight= ui->btnRight->height();
    int wBtnUp = ui->btnUp->width();
    int lBtnUp= ui->btnUp->height();
    int wBtnDown = ui->btnDown->width();
    int lBtnDown= ui->btnDown->height();


    QPixmap scaledL = pixL.scaled(wBtnLeft,lBtnLeft,Qt::KeepAspectRatio);
    QPixmap scaledR = pixR.scaled(wBtnRight,lBtnRight,Qt::KeepAspectRatio);
    QPixmap scaledU = pixU.scaled(wBtnUp,lBtnUp,Qt::KeepAspectRatio);
    QPixmap scaledD = pixD.scaled(wBtnDown,lBtnDown,Qt::KeepAspectRatio);



    QIcon ButtonIconL(scaledL);
    QIcon ButtonIconR(scaledR);
    QIcon ButtonIconU(scaledU);
    QIcon ButtonIconD(scaledD);

    ui->btnLeft->setIcon(ButtonIconL);
    ui->btnRight->setIcon(ButtonIconR);
    ui->btnUp->setIcon(ButtonIconU);
    ui->btnDown->setIcon(ButtonIconD);

    ui->led_red->setPixmap(pixLR.scaled(20,20,Qt::KeepAspectRatio));
    ui->led_blue->setPixmap(pixLB.scaled(20,20,Qt::KeepAspectRatio));
    ui->led_green->setPixmap(pixLG.scaled(20,20,Qt::KeepAspectRatio));

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(breathpacer);

    timer = new QTimer(this);

    settings = new Settings();

    // creating history list
    h = new History();
    ui->summaryList->setSelectionMode(QAbstractItemView::SingleSelection);
    // connecting buttons

    connect(ui->btnMenu, SIGNAL(pressed()), this, SLOT(on_btnMenu_clicked()));
    connect(ui->btnBreathMenu, SIGNAL(pressed()), this, SLOT(on_btnMenu_clicked()));
    connect(ui->btnSetMenu, SIGNAL(pressed()), this, SLOT(on_btnMenu_clicked()));
    connect(ui->createSummary, SIGNAL(pressed()), this, SLOT(randomSummary()));
    connect(ui->reset, SIGNAL(pressed()), this, SLOT(reset()));
    connect(ui->remove, SIGNAL(pressed()), this, SLOT(deleteSummary()));
    connect(ui->view, SIGNAL(pressed()), this, SLOT(viewSummary()));
    connect(ui->btnHistoryMenu, SIGNAL(pressed()), this, SLOT(on_btnMenu_clicked()));
    connect(ui->btnSummaryMenu, SIGNAL(pressed()), this, SLOT(on_btnMenu_clicked()));
    connect(ui->btnBack, SIGNAL(pressed()), this, SLOT(on_back_clicked()));

    Coherence *c = new Coherence();
    summary = new Summary(0, c);
    // connecting signal to open Summary window screen whenever it needs to be called
    connect(this, SIGNAL(summaryReady(Summary*)), this, SLOT(displaySummary(Summary*)));


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSettings_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSettings);
}

void MainWindow::on_btnChallenge_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->pageChallenge);
}

void MainWindow::on_btnGoToBreath_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->pageBreath);
}

void MainWindow::on_btnMenu_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_back_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageHistory);
}

void MainWindow::on_btnSelector_clicked()
{

   if(on == true){
       if(sessionStarted==false){
            sessionStarted = true;
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(update())); timer->start(1000);
            connect(timer, &QTimer::timeout, this, &MainWindow::updateProgress);
            timer->start(1000);
            session = new Session(settings->getChallengeLevel());
        }
        else{
            sessionStarted = false;
            sec = 0;
            timer -> stop();
            ui->progressBar->setValue(0);
            summary = new Summary(settings->getChallengeLevel(),session->getCoherence());
            h->addSummary(summary);
            emit summaryReady(summary);
            delete session;
        }

}

}
void MainWindow::on_btnOn_clicked()
{
    if(on==false){

        on = true;
        ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    }
    else{
        on = false;
        ui->stackedWidget->setCurrentWidget(ui->page_Off);




        /*ui->lblLength->setText(QVariant(sec).toString());
        if(!(sec == 0)){
            timer ->stop();
        }*/
         ui->progressBar->setValue(0);
         sec = 0;

//         // ~Argyle
//         if(chart->getStatus() == 1){
//             chart->stopTimer();
//             chart->setStatus(0);
//         }

    }
}

/*void MainWindow::update(){
    sec++;
    ui->lblLength->setText(QVariant(sec).toString());
}*/

void MainWindow::on_btnLog_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageHistory);
}

void MainWindow::updateProgress()
{
    ui->progressBar->setValue(ui->progressBar->value()+1);
    if( ui->progressBar->value()== 10){
        ui->progressBar->setValue(0);

    }
}

void MainWindow::on_btnDone_clicked()
{
    int level = 0;
    if(ui->btnL1->isChecked() == true){
        level = 1;
    }
    else if(ui->btnL2->isChecked() == true){
        level = 2;
    }
    else if(ui->btnL3->isChecked() == true){
        level = 3;
    }
    else if(ui->btnL4->isChecked() == true){
        level = 4;
    }

    if(!(level == 0)){
        settings -> setChallengeLevel(level);
    }

    ui->stackedWidget->setCurrentWidget(ui->pageMenu);


}

void MainWindow::on_btnBreath_clicked()
{



   if((ui->txtBreath->text()).toInt() < 31 && (ui->txtBreath->text()).toInt()>0 && !((ui->txtBreath->text()).isEmpty())){
       settings->setBreathPacer((ui->txtBreath->text()).toInt());
   }


   ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_btnNewSession_clicked()
{
    session = new Session(settings->getChallengeLevel());
    // ~ Argyle
    qDebug() << "new session";
    ui->stackedWidget->setCurrentWidget(ui->pageSessionChart);

    Chart *chart = new Chart();
    chart->setLED(ui->readingLED);
    chart->setCohLabel(ui->cohChartLabel);
    chart->setLenLabel(ui->lenChartLabel);
    chart->setAchLabel(ui->achChartLabel);
    chart->resize(481,301);
    chart->setStatus(1);// testing purposes
    chart->setMode(2);// testing

    chart->setTitle("HRV vs. Time (s)");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QVector<qint32> rrIntArr;

    DirHelp *dirHelp = new DirHelp("teamproject_3004");
    dirHelp->readTextFileIntoVectorArray("rrdata1.txt", &rrIntArr);
    chart->setCurrRRIntArr(rrIntArr);
    chart->i = new QVectorIterator<qint32>(chart->getCurrRRIntArr());

    chart->startTimer();
    chart->printCurrRRIntArr();

}

void MainWindow::randomSummary() {
    qDebug() << "Created random summary";
    QRandomGenerator gen;
    int challengeLevel = gen.generate() % 4 + 1;

    Coherence *c = new Coherence();
    float greenScore = (gen.generate() % 210)/(gen.generate() % 7);
    c->setGreenScore(greenScore);

    float blueScore = (gen.generate() % 210)/(gen.generate() % 7);
    c->setBlueScore(blueScore);

    float redScore = (gen.generate() % 210)/(gen.generate() % 7);
    c->setRedScore(redScore);

    c->setScore(greenScore + blueScore + redScore);


    int greenTime = (gen.generate() % 64 + 1);
    int blueTime = (gen.generate() % 64 + 1);
    int redTime = (gen.generate() % 64 + 1);

    c->setGreenTime(greenTime);
    c->setBlueTime(blueTime);
    c->setRedTime(redTime);
    c->setTime(greenTime + blueTime + redTime);


    // Create the Summary object with the random values
    summary = new Summary(challengeLevel, c);

    qDebug() << "Summary created, will attempt to display";
    emit summaryReady(summary);
    h->addSummary(summary);
    updateHistory();
    qDebug() << "Added summary to history";
}

void MainWindow::displaySummary(Summary* s) {

    QString challengeLevel = QString::number(s->getCLevel());
    ui->cLevelVal->setText(challengeLevel);

    QString green = QString::number(s->getGreenPercent(), 'f', 2) + '%';
    ui->greenCohVal->setText(green);

    QString blue = QString::number(s->getBluePercent(), 'f', 2) + '%';
    ui->blueCohVal->setText(blue);

    QString red = QString::number(s->getRedPercent(), 'f', 2) + '%';
    ui->redCohVal->setText(red);

    QString avg = QString::number(s->getAvgC(), 'f', 2);
    ui->avgCohVal->setText(avg);

    QString time = QString::number(s->getTime());
    ui->sessionLenVal->setText(time);

    QString score = QString::number(s->getScore(),'f',2);
    ui->achieveScoreVal->setText(score);

    QString date = s->getDate().toString();
    ui->dateVal->setText(date);

    ui->stackedWidget->setCurrentWidget(ui->pageSummary);
}

void MainWindow::endSession(int level, Coherence *c) {
    // Create the Summary object with the random values
    summary = new Summary(level, c);
    emit summaryReady(summary);

    h->addSummary(summary);
    updateHistory();
}

void MainWindow::updateHistory() {

    ui->summaryList->clear();

    for (int i = 0; i < h->getHistory().size(); i++) {
        Summary* s = h->getHistory().at(i);
        QString title = s->getDate().toString();
        QListWidgetItem* item = new QListWidgetItem(title,ui->summaryList);
    }
}

void MainWindow::reset() {
    h->clearData();
    updateHistory();
    // breathpacer = 10;
    // challengeLevel = 1;
}

void MainWindow::deleteSummary() {
    if(ui->summaryList->currentIndex().isValid()) {
        int index = ui->summaryList->currentRow();
        h->removeSummary(index);
        updateHistory();
    }
}

void MainWindow::viewSummary() {
    if(ui->summaryList->currentIndex().isValid()) {
        int index = ui->summaryList->currentRow();
        Summary *s = h->getSummary(index);
        emit summaryReady(s);
    }
}
