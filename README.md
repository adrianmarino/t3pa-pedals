# T3PA Pedals Firmware

Android firmware that allows convert `T3PA Pedals` to `USB`. It allows to use `T3PA Pedals` with other wheel bases as a regular 3 axis joystick. 


<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/T3PA-Pedals.jpg?raw=true"  height="500" />
</p>


## Dependencies

- [Joystick](https://github.com/gmarty2000-ARDUINO/arduino-JOYSTICK)
- [EWMA](https://github.com/jonnieZG/EWMA)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [EPROM](https://docs.arduino.cc/learn/built-in-libraries/eeprom/)


## Hardware

* [Arduino Leonardo compatible board with **Atmega32u4** chipset](https://protosupplies.com/product/pro-micro-5v-16mhz/). **Atmega32u4** supports HID interface via USB. Arduino pro micro is an excellent selection because is a very tiny board.


<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/arduino-pro-micro-board.png?raw=true"  height="330" />
</p>

* `3` x 0.2 µF capasitors.


<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/capasitor.webp?raw=true"  height="200" />
</p>


## Settings

You can config pedals via serial terminal.


1. Open a serial terminal to `COM4`(windows) or `/dev/ttyACM0`(linux) ports.

2. Show help with `help` command:

    ```bash
    13:19:54.148 -> -----------------------------------------------------------
    13:19:54.148 ->  T3PA - Pedals
    13:19:54.148 -> -----------------------------------------------------------
    13:19:54.148 -> You can modify settings by sending a JSON to device. You
    13:19:54.148 -> can also read current settings. All settings are saved
    13:19:54.148 -> into device internal memory.
    13:19:54.148 -> -----------------------------------------------------------
    13:19:54.148 -> Options:
    13:19:54.148 -> 
    13:19:54.148 -> 1. Use 'show' command to see current settings.
    13:19:54.148 -> 2. Send a json to update settings.
    13:19:54.148 -> -----------------------------------------------------------
    ```

3. See current config with `show` command:

    ```bash
    13:19:50.365 -> Settings:
    13:19:50.365 -> {
    13:19:50.365 ->   "clutch_smoothing_factor": 0.99,
    13:19:50.365 ->   "break_smoothing_factor": 0.99,
    13:19:50.365 ->   "throttle_smoothing_factor": 0.99
    13:19:50.365 -> }
    ```


4. Change settings with a `json` command:

    Command:
    ```json
    {"clutch_smoothing_factor": 0.95, "break_smoothing_factor": 0.95, "throttle_smoothing_factor": 0.95}
    ```

    Output:
    
    ```bash
    13:22:58.262 -> Loading json settings...
    13:22:58.262 -> Appling settings...
    13:22:58.262 -> Saving settings...
    13:22:58.294 -> Settings:
    13:22:58.294 -> {
    13:22:58.294 ->   "clutch_smoothing_factor": 0.95,
    13:22:58.294 ->   "break_smoothing_factor": 0.95,
    13:22:58.294 ->   "throttle_smoothing_factor": 0.95
    13:22:58.294 -> }
    ```


## Make seetings via `SerialPort` python class

See [example notebook](https://github.com/adrianmarino/t3pa-pedals/blob/master/notebook.ipynb)
