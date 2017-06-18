
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

class Bluetooth {

  public:
    void Setup();
    void Run();
    void Print(String frase);
    void setColor(int vPin, char color);
    void writeValue(int pinValue, bool num);
    int joystickLR;                           //joystick left & right
    int joystickUD;                           //joystick up & down

  private:
    char auth[] = "cb3191e6071f48cfae4753c8d88f405e";
};

extern Bluetooth myJoystick;

#endif
