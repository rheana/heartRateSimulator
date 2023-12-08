#ifndef SUMMARY_H
#define SUMMARY_H

using namespace std;
#include "session.h"
#include <QDateTime>
#include <QObject>
#include <QDebug>

class Summary : public QObject {

    Q_OBJECT

    public:
        Summary(int, Coherence*);        // constructor
        ~Summary();                     // destructor

        int getID() {return summaryID;}
        int getCLevel() {return challengeLevel;}
        float getBluePercent() {return 100 * coherence->getBlueTime() / coherence->getTotalTime();}
        float getGreenPercent() {return 100 * coherence->getGreenTime() / coherence->getTotalTime();}
        float getRedPercent() {return 100 * coherence->getRedTime() / coherence->getTotalTime();}
        float getAvgC() {return avgCoherence;}
        int getTime() {return coherence->getTotalTime();}
        float getScore() {return coherence->getTotalScore();}
        QDateTime getDate() {return dateT;}
        // void getChart() {return chart;}

        void sendSummary();

    private:

        static int summaryID;           // summary id
        int challengeLevel;             // session challenge level
        Coherence *coherence;           // object to store coherence sums and times
        float avgCoherence;             // average of coherence
        QDateTime dateT;                // date and time summary is created
        // Chart chart

};

#endif
