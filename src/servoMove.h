
#ifndef SERVO_MOVE_H
#define SERVO_MOVE_H
#include "bluetooth.h"
#include "timeDelay.h"

class servo : public Bluetooth, public timeDelay {

  public:
    void servoSetup();
    void servoRead();
    void servoMove(int *finalPos);
    byte getSpeed();
    char getDir();

#define HOMEPOSY 90
#define HOMEPOSZ 90
    int finalPosC[13] = {HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY - 20, HOMEPOSY + 30, HOMEPOSY - 20, HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY - 20, HOMEPOSY + 30, HOMEPOSY - 20, 10};
    int finalPosD[13] = {HOMEPOSZ - 30, HOMEPOSZ, HOMEPOSZ - 30, HOMEPOSY, HOMEPOSY, HOMEPOSY, HOMEPOSZ, HOMEPOSZ - 30, HOMEPOSZ, HOMEPOSY, HOMEPOSY, HOMEPOSY, 10};
    int finalPosB[13] = {HOMEPOSZ, HOMEPOSZ - 30, HOMEPOSZ, HOMEPOSY, HOMEPOSY, HOMEPOSY, HOMEPOSZ - 30, HOMEPOSZ, HOMEPOSZ - 30, HOMEPOSY, HOMEPOSY, HOMEPOSY, 10};
    int finalPosA[13] = {HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY + 20, HOMEPOSY - 30, HOMEPOSY + 20, HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY + 20, HOMEPOSY - 30, HOMEPOSY + 20, 10};
    int finalPosH[13] = {HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY + 20, HOMEPOSY - 30, HOMEPOSY + 20, HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY - 20, HOMEPOSY + 30, HOMEPOSY - 20, 10};
    int finalPosI[13] = {HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY - 20, HOMEPOSY + 30, HOMEPOSY - 20, HOMEPOSZ, HOMEPOSZ, HOMEPOSZ, HOMEPOSY + 20, HOMEPOSY - 30, HOMEPOSY + 20, 10};

  private:
    bool delayDone;
    bool positionOk;
    int myservo_pos[12];
    int diff[12];
    int maxDiff;
    char dir;
    int var;
    int moveDelay = 30;
    int v1;
    int v2;

};
#endif
