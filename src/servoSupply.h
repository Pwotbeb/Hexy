
#ifndef SERVO_SUPPLY_H
#define SERVO_SUPPLY_H
#include "bluetooth.h"

class supply : public Bluetooth {

  public:
    void supplySetup();                        //inizializza i pin ultilizzati per l'alimentazione
    float getVoltage();                        //funzione che legge e restituisce la tensione di una sola cella della batteria LiPo
    byte getDutyCicle();                        //funzione che in base alla tensione della batteria restituisce il valore del duty cicle fra 0 e 255
    void pwmMos();                             //funzione che gestisce il mosfet in pwm a 62500Hz (valore dutyCicle in ingresso deve essere compreso fra 0 e 255)

  private:
#define batteryPin A1
#define mosPin 3                                  //pin 3 obbligatorio per l'uso del Timer2
#define lipoCells 2                               //numero di celle della batteria LiPo (min 2)
#define batteryVpin A5                            // pin virtuale di Blynk al quale è connesso il display level
#define supplyValue 6                             //voltaggio voluto per l'alimentazione
    int voltage;
    int scaledVoltage;
    float battVoltage;
    float dutyCicle;
    byte scaled_dutyCicle;
};

#endif
