# Thrustmaster T3PA Pedals USB Firmware

Arduino firmware that allows convert `T3PA Pedals` to `USB`. It allows to use `T3PA Pedals` with other wheel bases as a regular 3 axis joystick. 
Is important note that **this firmware allows to convert any pedals to `USB` or build your own pedals and use it through `USB` port as a regular 3 axis joystick**. Both the circuit and firmware are agnostic, could be used for any pedals project.

<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/T3PA-Pedals.jpg?raw=true"  height="630" />
</p>


## Requisites

* [Arduino IDE](https://www.arduino.cc/en/software)
* `jupyterlab` (Optional)
* `pysearial` (Optional)
* [anaconda](https://www.anaconda.com/products/individual) / [miniconda](https://docs.conda.io/en/latest/miniconda.html) / [mamba](https://github.com/mamba-org/mamba) (Optional)

## Firmware dependencies

- [Joystick](https://github.com/gmarty2000-ARDUINO/arduino-JOYSTICK)
- [EWMA](https://github.com/jonnieZG/EWMA)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [EPROM](https://docs.arduino.cc/learn/built-in-libraries/eeprom/)


## Hardware

* [Arduino Leonardo compatible board with **Atmega32u4** chipset](https://protosupplies.com/product/pro-micro-5v-16mhz/). **Atmega32u4** supports HID interface via USB. Arduino pro micro is an excellent selection because is a very tiny board.


<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/arduino-pro-micro-board.png?raw=true"  height="330" />
</p>

* `3` x 0.2 µF capasitors. Used to remove electric noise from arduino analog inputs (`A0`, `A1` and `A2`).


<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/capasitor.webp?raw=true"  height="200" />
</p>


## Circuit

<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/Pedal-Circuit.png?raw=true"  height="500" />
</p>


## Settings

You could change `T3PA Pedals` settings via `serial terminal`.

1. Open a `serial terminal` and make a conection with `COM4`(windows) or `/dev/ttyACM0`(linux) ports at `9600` baud.


2. Press all pedals at same time to enter to **config mode**. You should see the following message on the serial terminal:

    ```bash
    Config mode: ON
    ```

2. See help with `help` command:

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
    13:19:54.148 -> 3. Use 'off' command to finish config mode..
    13:19:54.148 -> -----------------------------------------------------------
    ```

3. See current settings with `show` command:

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


**Important**: The firmware apply an **[Exponentially Weighted Moving Average (EWMA)](https://www.youtube.com/watch?v=XV1f_srZg_E)** to each pedal. EWMA use a **Smoothing Factor**. It factor control de average level over each pedal signal. Higher the value, less smoothing (higher the latest reading impact). See [EWMA](https://github.com/jonnieZG/EWMA) for more details.


5. Finish config mode with `off` command:

    ```bash
    Config mode: OFF
    ```

**Important**: `Config mode` allows minimize pedal input lag, because there is no waiting to receive serial commands. It increase execution time on main program loop.


## Change settings via `SerialPort` python class

### See [example notebook](https://github.com/adrianmarino/t3pa-pedals/blob/master/notebook.ipynb)

### Setup python env and run notebook

1. Create python env and install required libraries.

    ```bash
    conda create -n t3pa
    conda install pyserial
    conda install jupyterlab
    ```

2. Enable python env.

    ```bash
    conda activate t3pa
    ```

3. Open jupyterlab

    ```bash
    jupyter lab
    ```

4. Open and run `notebook.ipynb`

