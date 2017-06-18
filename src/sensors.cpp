
#include <Arduino.h>
#include <Wire.h>
#include "sensors.h"

void sensors::sensorSetup() {

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Wire.begin();
  Wire.beginTransmission(MPUaddress);   //inizializza la connessione con l'accelerometro
  Wire.write(0x6B);                     //PWR_MGMT_1 register
  Wire.write(0);                        //inizializzazione MCU6050
  Wire.endTransmission(true);           //invio un messaggio di stop trasmissione

  Serial.println("Sensors READY");
  Print("-> Sensors READY");
}

float sensors::getTemperature() {

  Wire.beginTransmission(MPUaddress);
  Wire.write(0x41);                       //inizia leggendo il registro della temperatura
  Wire.endTransmission(false);
  Wire.requestFrom(MPUaddress, 2, true);  //richiede all'indirizzo del giroscopio 2 bytes

  temp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  return (temp / 340.00 + 36.53);
}

float sensors::getSoundSpeed() {

  soundSpeed = (331, 45 + (0, 62 * temp)) * 10000;   // 331,45 = velocità del suono a 0° --- 0,62 = costante di variazione velocità del suono
  //moltiplico per 10000 per convertire da m/s in cm/us
  return soundSpeed;
}

long sensors::getDistance() {

  do {
    digitalWrite(triggerPin, HIGH);                 //invio un impulso di 10us al sensore per fare la misura
  }
  while (microsDelay(10) == 0);

  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);                //leggo la durata dell'impulso che mi restituisce il sensore
  distance = (getSoundSpeed() * duration);      //calcolo la distanza con la formula S=V*t

  return distance;
}

float sensors::getGyroscope (char axes) {          //funzione per la lettura dei dati del giroscopio

  Wire.beginTransmission(MPUaddress);
  Wire.write(0x43);                       //inizia leggendo il registro del giroscopio X
  Wire.endTransmission(false);
  Wire.requestFrom(MPUaddress, 6, true);  //richiede all'indirizzo del giroscopio 6 bytes (due byte per ogni asse)

  gyroValueX = Wire.read() << 8 | Wire.read();
  gyroValueY = Wire.read() << 8 | Wire.read();
  gyroValueZ = Wire.read() << 8 | Wire.read();

  switch (axes) {                         //in base al carattere inserito nella funzione restituisco il relativo dato

    case 'X':
      return gyroValueX;
      break;

    case 'Y':
      return gyroValueY;
      break;

    case 'Z':
      return gyroValueZ;
      break;

    default:                                        //se non viene inserito alcun carattere nella funzione, restituisco tutti i dati nell'ordine XYZ
      return gyroValueX, gyroValueY, gyroValueZ;
      break;
  }
}

float sensors::getAccelerometer (char axes) {     //funzione per la lettura dei dati dell'accelerometro

  Wire.beginTransmission(MPUaddress);
  Wire.write(0x3B);                       //inizia leggendo il registro dell'accelerometro X
  Wire.endTransmission(false);
  Wire.requestFrom(MPUaddress, 6, true);  //richiede all'indirizzo dell'accelerometro 6 bytes (due byte per ogni asse)

  accValueX = Wire.read() << 8 | Wire.read();
  accValueY = Wire.read() << 8 | Wire.read();
  accValueZ = Wire.read() << 8 | Wire.read();

  switch (axes) {                         //in base al carattere inserito nella funzione restituisco il relativo dato

    case 'X':
      return accValueX;
      break;

    case 'Y':
      return accValueY;
      break;

    case 'Z':
      return accValueZ;
      break;

    default:                                        //se non viene inserito alcun carattere nella funzione, restituisco tutti i dati nell'ordine XYZ
      return accValueX, accValueY, accValueZ;
      break;
  }
}

