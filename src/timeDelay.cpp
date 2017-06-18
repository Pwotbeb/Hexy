
#include <Arduino.h>
#include "timeDelay.h"

bool timeDelay::millisDelay(unsigned long intervalDelay) {

  delayDone1 = 0;
  previousMillis = millis();

  while (delayDone1 == 0) {
    if (millis() >= previousMillis + intervalDelay) {        //verifica se è trascorso il delay
      delayDone1 = 1;
      return 1;
    }
    else if (millis() <= (-(4294967295 - previousMillis) + intervalDelay)) {   //controlla se la funzione millis va in overflow
      if (millis() + (4294967295 - previousMillis >= intervalDelay)) {
        return 1;
      }
    }
  }
}

bool timeDelay::microsDelay(unsigned long intervalDelay) {

  delayDone2 = 0;
  previousMicros = micros();

  while (delayDone2 == 0) {
    if (micros() >= previousMicros + intervalDelay) {        //verifica se è trascorso il delay
      delayDone2 = 1;
      return 1;
    }
    else if (micros() <= (-(4294967295 - previousMicros) + intervalDelay)) {   //controlla se la funzione millis va in overflow
      if (micros() + (4294967295 - previousMicros >= intervalDelay)) {
        return 1;
      }
    }
  }
}
