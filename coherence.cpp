#include "coherence.h"

// constructor
Coherence::Coherence() {
    greenScore = 0;
    greenTime = 0;

    blueScore = 0;
    blueTime = 0;

    redScore = 0;
    redTime = 0;

    totalScore = 0;
    totalTime = 0;
}

// destructor
Coherence::~Coherence() {

}

void Coherence::updateGreen(float score) {
    greenScore += score;
    totalScore += score;
    status = "green";
    greenTime += 5;
    totalTime += 5;
}

void Coherence::updateBlue(float score) {
    blueScore += score;
    totalScore += score;
    status = "blue";
    blueTime += 5;
    totalTime += 5;
}

void Coherence::updateRed(float score) {
    redScore += score;
    totalScore += score;
    status = "red";
    redTime += 5;
    totalTime += 5;
}
