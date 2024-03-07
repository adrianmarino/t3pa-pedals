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

1. Open a `serial terminal` with [Putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) and make a conection with `COM`(windows) or `/dev/ttyACM0`(linux) ports **[1]** at `9600` baud **[2]**.


<p align="center">
  <img src="https://github.com/adrianmarino/t3pa-pedals/blob/master/images/putty.png?raw=true"  height="600" />
</p>

2. Press all pedals at same time to enter to **config mode**. You should see the following message on the serial terminal:

    ```bash
    Config mode: ON
    ```

2. See help with `help` command:

    ```bash
    -----------------------------------------------------------
    T3PA - Pedals
    -----------------------------------------------------------
    You can modify settings by sending a JSON to device. You
    can also read current settings. All settings are saved
    into device internal memory.
    -----------------------------------------------------------
    Options:
     
    1. Use 'show' command to see current settings.
    2. Send a json to update settings.
    3. Use 'off' command to finish config mode.
    -----------------------------------------------------------
    ```

3. See current settings with `show` command:

    ```bash
    Settings:
    {
      "clutch_smoothing_factor": 0.99,
      "break_smoothing_factor": 0.99,
      "throttle_smoothing_factor": 0.99
    }
    ```


4. Change settings with a `json` command:

    Command:
    ```json
    {"clutch_smoothing_factor": 0.95, "break_smoothing_factor": 0.95, "throttle_smoothing_factor": 0.95}
    ```

    Output:
    
    ```bash
    Loading json settings...
    Appling settings...
    Saving settings...
    Settings:
    {
      "clutch_smoothing_factor": 0.95,
      "break_smoothing_factor": 0.95,
      "throttle_smoothing_factor": 0.95
    }
    ```


**Important**: The firmware applies an **[Exponentially Weighted Moving Average (EWMA)](https://www.youtube.com/watch?v=XV1f_srZg_E)** to each pedal. EWMA uses a **Smoothing Factor** to control the average level over each pedal signal. The higher the value, the less smoothing (higher impact of the latest reading). For more details, see [EWMA](https://github.com/jonnieZG/EWMA). In this project, EWMA is primarily used as a method to eliminate electrical noise on analog inputs, finding a curve that fits better to the input data points detected in analog inputs.


5. Finish config mode with `off` command:

    ```bash
    Config mode: OFF
    ```
**Important:** The `Config mode` minimizes pedal input lag by eliminating the need to wait for serial commands. This mode increase the execution time in the main program loop.


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

