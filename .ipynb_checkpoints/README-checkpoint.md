# T3PA Pedal Firmware

Firmware required to make a USB a T3PA Pedal. 


## Dependencies
- [Joystick](https://github.com/gmarty2000-ARDUINO/arduino-JOYSTICK)
- [EWMA](https://github.com/jonnieZG/EWMA)

## Settings

You can config pedals via serial terminal.


1. Open a serial terminal to `COM4`(windows) or `/dev/ttyACM0`(linux) ports.

2. Show help with `help` command:

```
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

```
13:19:50.365 -> Settings:
13:19:50.365 -> {
13:19:50.365 ->   "clutch_smoothing_factor": 0.99,
13:19:50.365 ->   "break_smoothing_factor": 0.99,
13:19:50.365 ->   "throttle_smoothing_factor": 0.99
13:19:50.365 -> }
```


4. Change settings sending a json:

Command:
```
{"clutch_smoothing_factor": 0.95, "break_smoothing_factor": 0.95, "throttle_smoothing_factor": 0.95}
```

Output:

```
13:22:58.262 -> Load json settings
13:22:58.262 -> Apply settings
13:22:58.262 -> Set save settings
13:22:58.294 -> Settings:
13:22:58.294 -> {
13:22:58.294 ->   "clutch_smoothing_factor": 0.95,
13:22:58.294 ->   "break_smoothing_factor": 0.95,
13:22:58.294 ->   "throttle_smoothing_factor": 0.95
13:22:58.294 -> }
```