#include <Joystick.h>
#include <Ewma.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

Joystick_ Joystick;

#define CLUTCH A0
#define BREAK A1
#define THROTTLE A2

#define CLUTCH_ADDR 0
#define BREAK_ADDR  10
#define THROTTLE_ADDR 20

#define PEDAL_CONFIG_MODEL_LEVEL 150


Ewma *clutchFilter;
Ewma *breakFilter;
Ewma *throttleFilter;

static StaticJsonDocument<512> config;


boolean configMode = false;

float readFloatFromEprom(unsigned int addr) {
  union {
    byte b[4];
    float f;
  } data;
  
  for(int i = 0; i < 4; i++) {
    data.b[i] = EEPROM.read(addr+i);
  }
  return data.f;
}

void writeFloatToEprom(unsigned int addr, float x) {
  union {
    byte b[4];
    float f;
  } data;

  data.f = x;
  for(int i = 0; i < 4; i++) {
    EEPROM.write(addr+i, data.b[i]);
  }
}

void setupConfig() {
  float clutchFactor   = readFloatFromEprom(CLUTCH_ADDR);
  float breakFactor    = readFloatFromEprom(BREAK_ADDR);
  float throttleFactor = readFloatFromEprom(THROTTLE_ADDR);

  config["clutch_smoothing_factor"]   = clutchFactor;
  config["break_smoothing_factor"]    = breakFactor;
  config["throttle_smoothing_factor"] = throttleFactor;

  if (config["clutch_smoothing_factor"] == 0) {
    config["clutch_smoothing_factor"] = 0.9;
  } else {
    config["clutch_smoothing_factor"] = clutchFactor;    
  }

  if (config["break_smoothing_factor"] == 0) {
    config["break_smoothing_factor"] = 0.9;
  } else {
    config["break_smoothing_factor"] = breakFactor;    
  }

  if (config["throttle_smoothing_factor"] == 0) {
    config["throttle_smoothing_factor"] = 0.9;
  } else {
    config["throttle_smoothing_factor"] = throttleFactor;    
  }

  clutchFilter   = new Ewma(clutchFactor);
  breakFilter    = new Ewma(breakFactor);
  throttleFilter = new Ewma(throttleFactor);
}

boolean isConfigMode() {
  return getClutch() >= PEDAL_CONFIG_MODEL_LEVEL && 
  getBreak() >= 80 &&
  getThrottle() >= PEDAL_CONFIG_MODEL_LEVEL;
}

void updateConfig() {
  if (configMode == false && isConfigMode()) {
    configMode = true;
    Serial.println("Config mode: ON");
  }

  if (configMode == true) {
    if (Serial.available() > 0) {
      String value = Serial.readStringUntil('\n');
      value.trim();

      if (value.equals("help")) {
        Serial.println("-----------------------------------------------------------");
        Serial.println(" T3PA - Pedals");
        Serial.println("-----------------------------------------------------------");
        Serial.println("You can modify settings by sending a JSON to device. You"); 
        Serial.println("can also read current settings. All settings are saved");
        Serial.println("into device internal memory.");
        Serial.println("-----------------------------------------------------------");
        Serial.println("Options:");
        Serial.println();
        Serial.println("1. Use 'show' command to see current settings.");
        Serial.println("2. Send a json to update settings.");
        Serial.println("-----------------------------------------------------------");
      } else if (value.equals("off")) {
        configMode = false;
        Serial.println("Config mode: OFF");
      } else if (value.equals("show")) {
        Serial.println("Settings:");
        serializeJsonPretty(config, Serial);
        Serial.println();
      } else{
        Serial.println("Loading json settings...");
        const auto loadJsonError = deserializeJson(config, value);
  
        if (loadJsonError) {
          Serial.print(F("Fail to load json settings!"));
          Serial.println(loadJsonError.f_str());
        } else {
          float clutchFactor   = config["clutch_smoothing_factor"].as<float>();
          float breakFactor    = config["break_smoothing_factor"].as<float>();
          float throttleFactor = config["throttle_smoothing_factor"].as<float>();

          Serial.println("Appling settings...");
          clutchFilter   = new Ewma(clutchFactor);
          breakFilter    = new Ewma(breakFactor);
          throttleFilter = new Ewma(throttleFactor);

          Serial.println("Saving settings...");
          writeFloatToEprom(CLUTCH_ADDR,   clutchFactor);
          writeFloatToEprom(BREAK_ADDR,    breakFactor);
          writeFloatToEprom(THROTTLE_ADDR, throttleFactor);

          Serial.println("Settings:");
          serializeJsonPretty(config, Serial);
        }
      }
    }
  }
}

int readAnalogInput(int pin, int delayValue=1) {
  int value = map(analogRead(pin), 0, 1023, 0, 255);
  delay(delayValue);
  return value;
}


int getClutch() {
  return readAnalogInput(CLUTCH);
}

int getBreak() {
  return readAnalogInput(BREAK);
}

int getThrottle() {
  return readAnalogInput(THROTTLE);
}

void updateJoystick() {
  Joystick.setZAxis(int(clutchFilter->filter(getClutch())));
  Joystick.setRxAxis(int(breakFilter->filter(getBreak())));
  Joystick.setThrottle(int(throttleFilter->filter(getThrottle())));
}

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  setupConfig();
}

void loop(){
  updateJoystick();
  updateConfig();
  delay(1);
}
