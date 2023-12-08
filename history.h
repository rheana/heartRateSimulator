#ifndef HISTORY_H
#define HISTORY_H

using namespace std;
#include "summary.h"
#include <QList>

class History : public QObject {

    Q_OBJECT

    public:

        History();         // constructor
        ~History();        // destructor

        QList<Summary*> getHistory() {return summaryList;}
        Summary* getSummary(int);

        void addSummary(Summary*);
        void removeSummary(Summary*);
        void removeSummary(int);

        void clearData();

    private:

        QList<Summary*> summaryList;     // list of all the summaries

    signals:

};

#endif
