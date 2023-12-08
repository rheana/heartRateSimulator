#include "summary.h"

int Summary::summaryID = 0;

// constructor
Summary::Summary(int level, Coherence* c) {
    challengeLevel = level;
    coherence = c;
    avgCoherence = coherence->getTotalScore()/coherence->getTotalTime();
    dateT = QDateTime::currentDateTime();

    summaryID++; // create ID ordinally
}

// destructor
Summary::~Summary() {

}
