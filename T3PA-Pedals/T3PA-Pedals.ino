#include <Joystick.h>
#include <ArduinoJson.h>

Joystick_ Joystick;

#define CLUTCH A0
#define BREAK A1
#define THROTTLE A2

int readAnalogInput(int pin, int delayValue=1) {
  int value = map(analogRead(pin), 0, 1023, 0, 255);
  delay(delayValue);
  return value;
}

void setup() {
  Joystick.begin();
}

void loop(){
  Joystick.setZAxis(readAnalogInput(CLUTCH)); 
  Joystick.setRxAxis(readAnalogInput(BREAK));
  Joystick.setThrottle(readAnalogInput(THROTTLE));
  delay(1);
}
