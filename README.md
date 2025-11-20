# Tests

This folder contains very simple Arduino sketches I developed during my first year at university and as part of the robotics team to learn how to program hardware for the secondary robot in Eurobot 2024. They are component testing programs that also served as the foundation for the team’s private routines. Coming from a Python background, these examples helped me get started with C/C++. The complexity increases progressively, from basic switch and timing tests to examples using classes for an OLED display.

Important note on privacy
-------------------------
The sketches in this folder are component tests and demos. The team’s final routines and higher-level strategies are private and not included here. These files show low-level, introductory code only.

Contents
--------
- `DC_velocity_tester` — Test sketch for DC motor velocity. Use this to verify motor response and basic velocity behavior.
- `L298N_tester` — Simple tester for an L298N motor driver (basic motor control and direction tests).
- `Limit_switch_tester` — Reads and debounces a limit/safety switch for mechanical tests.
- `Millis_test` — Example of non-blocking timing using `millis()` instead of `delay()`.
- `Oled_display_tester` — Tests OLED display functions. The sketch displays the battery percentage and the current field color (H for homologation / B for blue / Y for yellow) on the screen.
- `Servo_tester` — Basic servo movement and calibration sketch.
- `Switch_tester` — Simple sketch to test push-buttons and switches.
- `Ultrasonic_tester` — Distance measurement using an ultrasonic sensor (HC‑SR04).

Prerequisites
-------------
- Arduino IDE (or compatible editor).
- Select the correct board and serial port in the IDE before uploading.
- Install libraries when required:
  - `Oled_display_tester` — Requires:
    - `Adafruit_GFX`
    - `Adafruit_SSD1306`

Hardware notes
--------------
- Before uploading code, verify that the pin assignments in the sketch match your hardware wiring and that all connections are secure.
- If a sketch uses `analogReference(EXTERNAL)`, ensure you actually provide the external reference voltage in hardware; otherwise use `DEFAULT`.
- Do not power motors or servos from USB or the Arduino 5V regulator while the board is connected to a computer. Instead, use a dedicated external power supply and connect the grounds for your computer's safety.

How to use
----------
1. Open the corresponding `.ino` file in the Arduino IDE.
2. Check the top-of-file comments for pin assignments and required connections.
3. Select the board and COM port, then click Upload.
4. Open the Serial Monitor (baud rate shown in the sketch, typically 9600) to view debug output.

Oled display image
------------------
<p align="center">
  <img src="images/display.jpg"/>
</p>

License & contact
-----------------
These sketches are educational examples I developed. If you need more details about wiring or to discuss a particular sketch, feel free to contact me via my GitHub profile.
