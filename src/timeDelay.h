
#ifndef TIME_DELAY_H
#define TIME_DELAY_H

class timeDelay {

  public:
    //le funzioni restituiscono 1 se il ritardo impostato è trascorso
    bool millisDelay(unsigned long intervalDelay);    //funzione di ritardo con gestione dell'overflow millis()
    bool microsDelay(unsigned long intervalDelay);    //funzione di ritardo con gestione dell'overflow micros()

  private:
    bool delayDone1;
    bool delayDone2;
    unsigned long previousMillis;
    unsigned long previousMicros;
};

#endif

