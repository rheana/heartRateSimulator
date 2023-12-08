#ifndef SETTINGS_H
#define SETTINGS_H
#include <QDebug>

class Settings
{
public:
    Settings();
    ~Settings();
    int getChallengeLevel();
    int getBreathPacer();
    void setChallengeLevel(int);
    void setBreathPacer(int);

private:
    int challengeLevel;
    int breathPacer;

};

#endif // SETTINGS_H
