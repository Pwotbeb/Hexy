
/*
   HEXY - Hexapod Robot Firmware - v3.4.1

   Copyright (C) 2016 - 2017 Luca Molettieri & Filippo Petri

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
*/

#include "servoSupply.h"
#include "servoMove.h"
#include "sensors.h"
#include "timeDelay.h"
#include "motion.h"
#include "bluetooth.h"

Bluetooth bluetooth;
sensors mySensors;
supply mySupply;
Hexy hexy;
servo myServos;

void setup() {

  Serial.begin (9600);
  bluetooth.Setup();
  mySupply.supplySetup();
  mySensors.sensorSetup();
  myServos.servoSetup();
  hexy.homePos();
}

void loop() {

  bluetooth.Run();
  hexy.motion();

}

