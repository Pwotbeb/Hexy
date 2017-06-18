
#include <Arduino.h>
#include "motion.h"

void Hexy::homePos() {
  servoMove(home_Pos);
}

void Hexy::up() {
  servoMove(up_Pos);
}

void Hexy::down () {
  servoMove(down_Pos);
}

void Hexy::walk_forward() {

  homePos();

  for (int i = 0; i < 3; i++) {

    servoMove(finalPosB);   // Stato B
    servoMove(finalPosC);   // Stato C
    servoMove(finalPosD);   // Stato D
    servoMove(finalPosA);   // Stato A
  }

  homePos();
}

void Hexy::walk_backward() {

  homePos();

  for (int i = 0; i < 3; i++) {
    servoMove(finalPosB);   // Stato B
    servoMove(finalPosA);   // Stato A
    servoMove(finalPosD);   // Stato D
    servoMove(finalPosC);   // Stato C
  }

  homePos();
}

void Hexy::rotate_left() {

  homePos();

  for (int i = 0; i < 2; i++) {
    servoMove(finalPosB);   // Stato B
    servoMove(finalPosI);   // Stato I
    servoMove(finalPosD);   // Stato D
    servoMove(finalPosH);   // Stato H
  }

  homePos();
}

void Hexy::rotate_right() {

  homePos();

  for (int i = 0; i < 2; i++) {
    servoMove(finalPosB);   // Stato B
    servoMove(finalPosH);   // Stato H
    servoMove(finalPosD);   // Stato D
    servoMove(finalPosI);   // Stato I
  }

  homePos();
}

void Hexy::motion() {

  input = getDir();
  Serial.println(input);

  if (currentState == 'B') {
    if (input == 'f') {       //forward
      nextState = 'C';
    }
    else if (input == 'b') {  //backward
      nextState = 'A';
    }
    else if (input == 'l') {  //left
      nextState = 'I';
    }
    else if (input == 'r') {  //right
      nextState = 'H';
    }
    else if (input == 's') {  //stop
      nextState = 'X';
    }
  }
  else if (currentState == 'C') {
    if (input == 'f' || input == 'l') {
      nextState = 'D';
    }
    else if (input == 'b' || input == 'r' || input == 's') {
      nextState = 'B';
    }
  }
  else if (currentState == 'D') {
    if (input == 'f') {
      nextState = 'A';
    }
    else if (input == 'b') {
      nextState = 'C';
    }
    else if (input == 'l') {
      nextState = 'H';
    }
    else if (input == 'r') {
      nextState = 'I';
    }
    else if (input == 's') {
      nextState = 'X';
    }
  }
  else if (currentState == 'A') {
    if (input == 'f' || input == 'l' || input == 's') {
      nextState = 'B';
    }
    else if (input == 'b' || input == 'r' ) {
      nextState = 'D';
    }
  }

  else if (currentState == 'I') {
    if (input == 'r' || input == 'b' || input == 's') {
      nextState = 'B';
    }
    else if (input == 'l' || input == 'f') {
      nextState = 'D';
    }
  }

  else if (currentState == 'H') {
    if (input == 'r' || input == 'b') {
      nextState = 'D';
    }
    else if (input == 'l' || input == 'f' || input == 's') {
      nextState = 'B';
    }
  }
  else if (currentState == 'X') {
    if (input == 'f' || input == 'b' || input == 'l' || input == 'r') {
      nextState = 'B';
    }
    else nextState = 'X';
  }

  if (nextState == 'C') {
    servoMove(finalPosC);                // Stato C
    currentState = 'C';
  }
  else if (nextState == 'D') {
    servoMove(finalPosD);                // Stato D
    currentState = 'D';
  }
  else if (nextState == 'B') {
    servoMove(finalPosB);                // Stato B
    currentState = 'B';
  }
  else if (nextState == 'A') {
    servoMove(finalPosA);                // Stato A
    currentState = 'A';
  }
  else if (nextState == 'H') {
    servoMove(finalPosH);                // Stato H
    currentState = 'H';
  }
  else if (nextState == 'I') {
    servoMove(finalPosI);                // Stato I
    currentState = 'I';
  }
  else if (nextState == 'X') {
    homePos();
    currentState = 'X';
  }
}

