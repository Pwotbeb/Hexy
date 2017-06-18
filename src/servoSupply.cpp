
#include <Arduino.h>
#include "servoSupply.h"
#include "bluetooth.h"

void supply::supplySetup() {

  pinMode (batteryPin, INPUT);
  pinMode (mosPin, OUTPUT);
  Serial.println("Supply READY");
  Bluetooth::Print("-> Supply READY");
}

float supply::getVoltage() {

  voltage = analogRead (batteryPin);                  //leggo la tensione con valore da 0 a 1023
  scaledVoltage = map (voltage, 0, 1023 , 0 , 500);   //trasformo il valore in un numero compreso fra 0 e 500
  //Blynk.virtualWrite(batteryVpin, scaledVoltage);   //invia al server di Blynk il valore letto della batteria

  if (scaledVoltage <= 280) {                         //se la tensione della cella è troppo bassa spengo l'alimentazione per prevenire danni alla batteria
    Serial.println("LOW BATTERY");
    digitalWrite(mosPin, LOW);
  }
  else {
    battVoltage = (scaledVoltage / 100) * lipoCells;  //divide per cento e moltiplica per il numero di celle della batteria
    return battVoltage;
  }
}

byte supply::getDutyCicle() {

  dutyCicle = (supplyValue / battVoltage) * 100;      //rapporto fra tensione voluta e duty cicle necessario per ottenerla
  scaled_dutyCicle = map(dutyCicle, 0, 100, 0, 255);  //trasformo il valore in un numero compreso fra 0 e 255

  return scaled_dutyCicle;
}

void supply::pwmMos() {

  TCCR2A = bit(COM2A1) | bit(COM2B1) | bit(WGM21) | bit(WGM20);   //registro A del Timer2
  TCCR2B = bit(WGM22) | bit(CS20);                                //registro B del Timer2
  OCR2A = 255;                                                    //frequenza = 16MHz / 0-255 (16MHz/255=62500Hz)
  OCR2B = scaled_dutyCicle;                                       //duty cicle 0-255
}

