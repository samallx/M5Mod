# Flashing ATtiny13A Using Arduino or ESP as ISP Programmer



## What You Need

| Item                      | Notes                                                             |
| ------------------------- | ----------------------------------------------------------------- |
| ATtiny13A chip            | Your target microcontroller                                       |
| Programmer                | Either **Arduino** (Uno, Nano, etc.) or **ESP** (ESP8266 / ESP32) |
| Breadboard & jumper wires | For wiring connections                                            |
| USB cable                 | To connect your programmer to PC                                  |
| AVR-GCC and AVRDUDE       | Installed on your PC (or use Arduino IDE)                         |



## Step 1: Prepare Your Programmer

| Programmer         | Instructions                                                                                                                                                                                                              |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Arduino as ISP** | 1. Connect Arduino to PC via USB.<br>2. Open Arduino IDE.<br>3. Load **File > Examples > 11.ArduinoISP > ArduinoISP**.<br>4. Upload the sketch to Arduino.                                                                |
| **ESP as ISP**     | 1. Connect ESP board to PC via USB.<br>2. Open Arduino IDE.<br>3. Upload a compatible **ArduinoISP sketch for ESP** (available online or ask me).<br>4. Make sure to note the GPIO pins used and baud rate in the sketch. |



## Step 2: Wire Your Programmer to the ATtiny13A

| ATtiny13A Pin | Arduino Pin    | ESP GPIO Pin (example)               |
| ------------- | -------------- | ------------------------------------ |
| Pin 1 (RESET) | Arduino Pin 10 | GPIO0                                |
| Pin 5 (MOSI)  | Arduino Pin 11 | GPIO13                               |
| Pin 6 (MISO)  | Arduino Pin 12 | GPIO12                               |
| Pin 7 (SCK)   | Arduino Pin 13 | GPIO14                               |
| Pin 4 (GND)   | Arduino GND    | GND                                  |
| Pin 8 (VCC)   | Arduino 5V     | 3.3V or 5V (check ESP voltage level) |



## Step 3: GET YOUR CODE READY

## Step 4: Compile Your Code to a `.hex` File

Run these commands in your terminal:

```bash
avr-gcc -mmcu=attiny13 -Os -o yourprogram.elf yourprogram.c
avr-objcopy -O ihex yourprogram.elf yourprogram.hex
```


## Step 5: Flash the `.hex` File to ATtiny13A

Run the following `avrdude` command. Replace `PORT` and `BAUDRATE` accordingly:

```bash
avrdude -c arduino -p attiny13 -P PORT -b BAUDRATE -U flash:w:yourprogram.hex
```

| Programmer  | Typical PORT                                     | Typical BAUDRATE               |
| ----------- | ------------------------------------------------ | ------------------------------ |
| Arduino ISP | `COM3` (Windows) or `/dev/ttyUSB0` (Linux/macOS) | 19200                          |
| ESP ISP     | ESP serial port (e.g., `/dev/ttyUSB0`)           | 115200 or 19200 (check sketch) |

---

## Step 6: Done!

Your ATtiny13A is now flashed and ready to run your custom code.


# Summary Table

| Step           | Arduino ISP                           | ESP ISP                                                                     |
| -------------- | ------------------------------------- | --------------------------------------------------------------------------- |
| Setup sketch   | Upload ArduinoISP sketch              | Upload ESP ArduinoISP sketch                                                |
| Wiring         | Use Arduino pins 10,11,12,13          | Use specified GPIO pins (e.g., 0,13,12,14)                                  |
| Voltage level  | 5V (Arduino 5V)                       | Usually 3.3V (check ATtiny specs!)                                          |
| Compile `.hex` | Same commands for both                | Same commands for both                                                      |
| Flash command  | `avrdude -c arduino -P COM3 -b 19200` | `avrdude -c arduino -P /dev/ttyUSB0 -b 115200` (baud depends on ESP sketch) |
