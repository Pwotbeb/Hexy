
#include <Arduino.h>
#include <Servo.h>
#include "servoMove.h"

#define HOMEPOSY 90       //posizione di home orizzontale in gradi
#define HOMEPOSZ 90       //posizione di home verticale in gradi
#define MINPOS 50         //posizione minima consentita
#define MAXPOS 160        //posizione massima consentita

Servo myservo[12];        //dichiarazione array di 12 servi

void servo::servoSetup() {                 //funzione per il setup dei servomotori

  myservo[0].attach(A0);      //servoRZ1
  myservo[1].attach(2);       //servoRZ2
  myservo[2].attach(4);       //servoRZ3
  myservo[3].attach(5);       //servoRY1
  myservo[4].attach(6);       //servoRY2
  myservo[5].attach(7);       //servoRY3
  myservo[6].attach(8);       //servoLZ1
  myservo[7].attach(9);       //servoLZ2
  myservo[8].attach(10);      //servoLZ3
  myservo[9].attach(11);      //servoLY1
  myservo[10].attach(12);     //servoLY2
  myservo[11].attach(13);     //servoLY3

  Serial.println("Servos READY");
  Bluetooth::Print("-> Servos READY");
}

void servo::servoRead() {                    //funzione per la lettura della posizione attuale dei 12 servomotori

  for (int i = 0; i <= 11; i++) {
    Serial.println(myservo[i].read());
  }
}

// funzione per il movimento simultaneo dei 12 servomotori con possibilità di regolazione della velocità di spostamento tramite l'impostazione di un delay

void servo::servoMove(int *finalPos) {        //funzione per il movimento dei servi alla velocità voluta

  delayDone = 1;
  positionOk = false;
  maxDiff = 0;

  for (int i = 0; i <= 11; i++) {                 //leggo la posizione attuale dei servi e la salvo nell'array myservo_pos
    myservo_pos[i] = myservo[i].read();
    diff[i] = (finalPos[i] - (myservo_pos[i]));   //ricavo la differenza tra posizione attuale e posizione finale
  }

  for (int i = 0; i <= 11; i++) {                 //ricavo il valore di differenza massima dell'array delle differenze
    if (maxDiff < abs(diff[i]))
      maxDiff = abs(diff[i]);
  }

  for (int d = 0; d <= 11; d++) {                 //verifico che la posizione voluta sia nel range prestabilito
    if (finalPos[d] > MAXPOS || finalPos[d] < MINPOS) {
      Serial.print ("Invalid position servo n. ");
      Serial.print (d);
      Serial.print (" (");
      Serial.print (finalPos[d]);
      Serial.println (") OPERATION ABORTED");
      positionOk = false;
    }
    else
      positionOk = true;
  }

  if (positionOk) {
    for (int i = 0; i <= maxDiff; i++) {
      if (delayDone == 1) {                       //la funzione restituisce 1 se il delay è trascorso, quindi quando il tempo del delay sarà passato pongo a 0 delayDone e continuo lo spostamento dei servomotori
        delayDone = 0;
        if (myservo_pos[0] != finalPos[0])        //se posizione attuale e posizione finale sono diverse e la differenza tra le due è maggiore di 0 incremento la posizione del servo, altrimenti la decremento
          (diff[0] > 0) ? myservo[0].write(myservo_pos[0]++) : myservo[0].write(myservo_pos[0]--);
        if (myservo_pos[1] != finalPos[1])
          (diff[1] > 0) ? myservo[1].write(myservo_pos[1]++) : myservo[1].write(myservo_pos[1]--);
        if (myservo_pos[2] != finalPos[2])
          (diff[2] > 0) ? myservo[2].write(myservo_pos[2]++) : myservo[2].write(myservo_pos[2]--);
        if (myservo_pos[3] != finalPos[3])
          (diff[3] > 0) ? myservo[3].write(myservo_pos[3]++) : myservo[3].write(myservo_pos[3]--);
        if (myservo_pos[4] != finalPos[4])
          (diff[4] > 0) ? myservo[4].write(myservo_pos[4]++) : myservo[4].write(myservo_pos[4]--);
        if (myservo_pos[5] != finalPos[5])
          (diff[5] > 0) ? myservo[5].write(myservo_pos[5]++) : myservo[5].write(myservo_pos[5]--);
        if (myservo_pos[6] != finalPos[6])
          (diff[6] > 0) ? myservo[6].write(myservo_pos[6]++) : myservo[6].write(myservo_pos[6]--);
        if (myservo_pos[7] != finalPos[7])
          (diff[7] > 0) ? myservo[7].write(myservo_pos[7]++) : myservo[7].write(myservo_pos[7]--);
        if (myservo_pos[8] != finalPos[8])
          (diff[8] > 0) ? myservo[8].write(myservo_pos[8]++) : myservo[8].write(myservo_pos[8]--);
        if (myservo_pos[9] != finalPos[9])
          (diff[9] > 0) ? myservo[9].write(myservo_pos[9]++) : myservo[9].write(myservo_pos[9]--);
        if (myservo_pos[10] != finalPos[10])
          (diff[10] > 0) ? myservo[10].write(myservo_pos[10]++) : myservo[10].write(myservo_pos[10]--);
        if (myservo_pos[11] != finalPos[11])
          (diff[11] > 0) ? myservo[11].write(myservo_pos[11]++) : myservo[11].write(myservo_pos[11]--);

        delayDone = millisDelay(finalPos[12]);    //cambiare finalpos[12] con getSpeed()
      }
    }
  }
}

/*byte servo::getSpeed() {

  var = abs(myJoystick.joystickUD);

  if (var >= 1 && var <= 32) {            //regolare valori delay
    moveDelay = 30;
  }
  else if (var >= 33 && var <= 64) {
    moveDelay = 25;
  }
  else if (var >= 65 && var <= 128) {
    moveDelay = 20;
  }
  else if (var >= 129 && var <= 192) {
    moveDelay = 15;
  }
  else if (var >= 193 && var <= 255) {
    moveDelay = 10;
  }
  return moveDelay;
  }*/

char servo::getDir() {

  v1 = myJoystick.joystickLR;
  v2 = myJoystick.joystickUD;

  // divisione dell'area del joystick tramite 2 rette di equazione y = x e y = -x
  // v1 = x, v2 = y

  if (v2 > v1 && v2 > -v1) {        //forward
    dir = 'f';
  }
  else if (v2 < v1 && v2 < -v1) {   //backward
    dir = 'b';
  }
  else if (v2 > v1 && v2 < -v1) {   //left
    dir = 'l';
  }
  else if (v2 < v1 && v2 > -v1) {   //right
    dir = 'r';
  }
  else if (v2 == 0 && v1 == 0) {    //stop
    dir = 's';
  }

  return dir;
}

