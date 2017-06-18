
#include <Arduino.h>
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>
#include "bluetooth.h"

#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT newSerial

SoftwareSerial newSerial(A2, A3); // RX, TX
WidgetTerminal terminal(V0);

Bluetooth myJoystick;

void Bluetooth::Setup() {

  newSerial.begin(9600);
  Blynk.begin(newSerial, auth);
  Serial.println("Bluetooth READY");
  terminal.println("-> Bluetooth READY");
  terminal.flush();           //controlla che i dati siano stati inviati al terminal
}

void Bluetooth::Run() {
  Blynk.run();
}

void Bluetooth::Print(String frase) {
  terminal.println(frase);
  terminal.flush();
}

void Bluetooth::setColor(int vPin, char color) {

  switch (color) {
    case 'R' :
      Blynk.setProperty(vPin, "color", "#FF0000");
      break;
    case 'G' :
      Blynk.setProperty(vPin, "color", "#00FF00");
      break;
    case 'B' :
      Blynk.setProperty(vPin, "color", "#0000FF");
      break;
    case 'Y' :
      Blynk.setProperty(vPin, "color", "#FFFF00");
      break;
  }
}

void Bluetooth::writeValue(int pinValue, bool num) {
  if (num == 0) {
    joystickLR = pinValue;
  }
  else if (num == 1) {
    joystickUD = pinValue;
  }
}

BLYNK_WRITE(V0) {   //funzione terminal

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  }
  else {
    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }
  // Ensure everything is sent
  terminal.flush();
}

BLYNK_WRITE(V1) {   //funzione joystick

  int x = param[0].asInt();
  int y = param[1].asInt();

  myJoystick.writeValue(x, 0);
  myJoystick.writeValue(y, 1);
}

