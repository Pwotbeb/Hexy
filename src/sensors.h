
#ifndef SENSORS_H
#define SENSORS_H
#include "bluetooth.h"
#include "timeDelay.h"

class sensors : public Bluetooth, public timeDelay {

  public:
    void sensorSetup();                             //inizializza i pin utilizzati per i sensori
    float getTemperature();                         //misura la temperatura dell'ambiente
    float getSoundSpeed();                          //calcola la velocità del suono in base alla temperatura ambientale
    long getDistance();                             //misura la distanza dagli ostacoli (in millimetri)
    float getGyroscope(char axes);                  //restituisce il valore dell'asse del giroscopio voluto
    float getAccelerometer (char axes);             //restituisce il valore dell'asse dell'accelerometro voluto

  private:
#define triggerPin 1
#define echoPin 2
#define MPUaddress 0x68                         //indirizzo I2C dell'accelerometro
    float temp;
    float soundSpeed;
    long distance;
    long duration;
    float gyroValueX;
    float gyroValueY;
    float gyroValueZ;
    float accValueX;
    float accValueY;
    float accValueZ;
};

#endif
