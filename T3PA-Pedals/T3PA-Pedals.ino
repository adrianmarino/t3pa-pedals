#include <Joystick.h>
#include <Ewma.h>

Joystick_ Joystick;

#define CLUTCH A0
#define BREAK  A1
#define GAS    A2
#define SAMPLE_SIZE 15

Ewma clutchFilter(0.5);
Ewma breakFilter(0.5);
Ewma gasFilter(0.5);


int readAnalogInput(int pin, int delayValue=1) {
  int value = map(analogRead(pin), 0, 1023, 0, 255);
  delay(delayValue);
  return value;
}

void setup() {
  Joystick.begin();
}

void loop(){
  int clutchValue = readAnalogInput(CLUTCH);
  int breakValue  = readAnalogInput(BREAK);
  int gasValue    = readAnalogInput(GAS);

  Joystick.setZAxis(int(clutchFilter.filter(clutchValue))); 
  Joystick.setRxAxis(int(breakFilter.filter(breakValue)));
  Joystick.setThrottle(int(gasFilter.filter(gasValue)));

  delay(3);
}
