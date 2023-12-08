#include "session.h"

// constructor
Session::Session(int level) {
    challengeLevel = level;
    coherence = new Coherence();
    // constructor for chart
}

// destructor
Session::~Session() {

}

void Session::scoreCalc() {


}

void Session::coherenceCalc(float score) {
    if (challengeLevel == 1) {
        if (score >= 0.5 && score <= 0.9) {
            coherence->updateBlue(score);
        } else if (score < 0.5 && score >= 0) {
            coherence->updateRed(score);
        } else if (score <= 16 && score > 0.9) {
            coherence->updateGreen(score);
        }
    }

    if (challengeLevel == 2) {
        if (score >= 0.6 && score <= 2.1) {
            coherence->updateBlue(score);
        } else if (score < 0.6 && score >= 0) {
            coherence->updateRed(score);
        } else if (score <= 16 && score > 2.1) {
            coherence->updateGreen(score);
        }
    }

    if (challengeLevel == 3) {
        if (score >= 1.8 && score <= 4) {
            coherence->updateBlue(score);
        } else if (score < 1.8 && score >= 0) {
            coherence->updateRed(score);
        } else if (score <= 16 && score > 4) {
            coherence->updateGreen(score);
        }
    }

    if (challengeLevel == 4) {
        if (score >= 4 && score <= 6) {
            coherence->updateBlue(score);
        } else if (score < 4 && score >= 0) {
            coherence->updateRed(score);
        } else if (score <= 16 && score > 6) {
            coherence->updateGreen(score);
        }
    }
}
