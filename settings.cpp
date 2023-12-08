#include "settings.h"
#include <QIntValidator>

Settings::Settings()
{
    challengeLevel = 1;
    breathPacer = 10;

}

Settings::~Settings()
{

}

int Settings::getChallengeLevel(){
    return challengeLevel;
}

int Settings::getBreathPacer(){
    return breathPacer;
}

void Settings::setChallengeLevel(int c){
    challengeLevel = c;

}
void Settings::setBreathPacer(int b){
    breathPacer = b;
}
