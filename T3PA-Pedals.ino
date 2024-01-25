#include <Joystick.h>

Joystick_ Joystick;

#define CLUTCH A0
#define BREAK  A1
#define GAS    A2
#define SAMPLE_SIZE 15

const bool initAutoSendState = true; 

int readAnalogInput(int pin, int delayValue=1) {
  int value = map(analogRead(pin), 0, 1023, 0, 255);
  delay(delayValue);
  return value;
}

void setup() {
  Joystick.begin();
}

void loop(){
  int clutchSum = 0;
  int breakSum  = 0;
  int gasSum    = 0;

  for (int s = 0; s < SAMPLE_SIZE; s++) {
    clutchSum += readAnalogInput(CLUTCH);
    breakSum  += readAnalogInput(BREAK);
    gasSum    += readAnalogInput(GAS);
  }

  Joystick.setZAxis(int(clutchSum / SAMPLE_SIZE)); 
  Joystick.setRxAxis(int(breakSum / SAMPLE_SIZE));
  Joystick.setThrottle(int(gasSum / SAMPLE_SIZE));

  delay(3);
}
