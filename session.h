#ifndef SESSION_H
#define SESSION_H

// #include "Chart.h"
#include "coherence.h"
#include <QDateTime>

class Session {

    public:

        Session(int);       // constructor
        ~Session();         // destructor

        Coherence* getCoherence() {return coherence;}

        void scoreCalc();           // calculate the score
        void coherenceCalc(float);  // calculate the coherence based on challenge level


    private:

        int challengeLevel;             // session challenge level
        float curScore;                 // current coherence score
        float achieveScore;             // total coherence score
        QTime sessionTime;              // duration of the session
        Coherence *coherence;            // object to store coherence sums and times
        // chart chart

};

#endif // SESSION_H
