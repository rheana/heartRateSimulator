#include "history.h"

// constructor
History::History() {

}

// destructor
History::~History() {
    for (int i = 0; i < summaryList.size(); i++) {
        delete summaryList[i];
    }
}

void History::addSummary(Summary* s) {
    if (summaryList.size() >= 256) {
        qInfo("Hit the summary limit, please delete some");
    } else {
        summaryList << s;
    }
}

void History::removeSummary(Summary* s) {
    int index = 0;

    for (; index < summaryList.size(); index++) {
        if (summaryList[index]->getID() == s->getID()) {
            break;
        }
    }

    summaryList.removeAt(index);
    delete s;
}

void History::removeSummary(int i) {
    Summary *s = summaryList[i];
    summaryList.removeAt(i);
    delete s;
}

Summary* History::getSummary(int i) {
    return summaryList[i];
}

void History::clearData() {
    summaryList.clear();
}
