#ifndef COHERENCE_H
#define COHERENCE_H

using namespace std;
#include <QString>>

class Coherence {

    public:

        Coherence();         // constructor
        ~Coherence();        // destructor

        float getGreenScore() {return greenScore;}
        float getBlueScore() {return blueScore;}
        float getRedScore() {return redScore;}

        float getTotalScore() {return totalScore;}
        int getTotalTime() {return totalTime;}

        int getGreenTime() {return greenTime;}
        int getBlueTime() {return blueTime;}
        int getRedTime() {return redTime;}

        // the following setters are for testing purposes only
        void setGreenScore(float s) {greenScore = s;}
        void setBlueScore(float s) {blueScore = s;}
        void setRedScore(float s) {redScore = s;}

        void setGreenTime(int t) {greenTime = t * 5;}
        void setBlueTime(int t) {blueTime = t * 5;}
        void setRedTime(int t) {redTime = t * 5;}

        void setScore(float s) {totalScore = s;}
        void setTime(int t) {totalTime = t * 5;}

        QString getStatus() {return status;}
        void setStatus(QString c) {status = c;}

        void updateGreen(float);
        void updateBlue(float);
        void updateRed(float);

    private:

        float greenScore;
        int greenTime;

        float blueScore;
        int blueTime;

        float redScore;
        int redTime;

        int totalScore;
        int totalTime;

        QString status;
};

#endif
