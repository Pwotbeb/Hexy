
#ifndef MOTION_H
#define MOTION_H
#include "servoMove.h"

class Hexy : public servo {

  public:
    void motion();
    void homePos();
    void up();
    void down();
    void walk_forward();
    void walk_backward();
    void rotate_right();
    void rotate_left();

  private:
    int home_Pos[13] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 20};
    int up_Pos[13] = {160, 160, 160, 90, 90, 90, 160, 160, 160, 90, 90, 90, 10};
    int down_Pos[13] = {50, 50, 50, 90, 90, 90, 50, 50, 50, 90, 90, 90, 10};
    char input;
    char currentState = 'X';
    char nextState;
};

#endif
