// This program displays information on an OLED screen to monitor battery level and field status.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Class to manage the OLED display
class OledDisplay {
public:
  Adafruit_SSD1306 oled;

  OledDisplay(uint8_t width, uint8_t height, TwoWire *wire, int8_t rst)
    : oled(width, height, wire, rst) {}

  void begin() {
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize the OLED display at address 0x3C
    oled.clearDisplay();                     // Clear the display
    oled.display();                          // Refresh the display
  }

  void show_battery(int bits, int percent) {
    oled.clearDisplay();                     // Clear the display
    oled.setTextColor(WHITE);                // White text
    oled.setCursor(10, 0);                   // Initial text position
    oled.setTextSize(1);                     // Small size for the title
    oled.print("Battery Percentage");      // Show the title
    oled.setCursor(117, 1);
    oled.print(":");

    // Draw battery frame
    oled.drawRect(22, 18, 84, 43, WHITE);    // Battery outline
    oled.fillRect(107, 29, 3, 22, WHITE);    // Battery terminal
    oled.fillRect(23, 19, bits, 42, WHITE);  // Fill according to level

    // Show centered percentage
    oled.fillRect(38, 25, 52, 29, BLACK);    // Black background for text
    center_text(percent);                     // Compute text position
    oled.setTextSize(2);                     // Large size for percentage
    oled.print(percent);
    oled.print("%");
    oled.display();                          // Refresh the display
  }

  void show_field_status(bool s1, bool s2) {
    oled.clearDisplay();                     // Clear the display
    oled.setTextColor(WHITE);                // White text
    oled.setCursor(10, 50);                  // Text position
    oled.setTextSize(1);                     // Small size

    if (!s1 && !s2) {
      Serial.println("Homologation");      // Status to serial
      oled.print("H");                     // Show H
    } else if (s1) {
      Serial.println("Blue");
      oled.print("B");
    } else {
      Serial.println("Yellow");
      oled.print("Y");
    }
    oled.display();                          // Refresh the display
  }

private:
  void center_text(int percent) {
    if (percent < 10)
      oled.setCursor(55, 32);                // Center for small values
    else if (percent == 100)
      oled.setCursor(42, 32);                // Center for 100%
    else
      oled.setCursor(49, 32);                // Center for normal values
  }
};

// Class to monitor the battery
class BatteryMonitor {
public:
  BatteryMonitor(int pin, float refV) : pin(pin), Vref(refV) {}

  void begin() {
    pinMode(pin, INPUT);                     // Configure the pin as input
    analogReference(EXTERNAL);               // External reference for ADC
  }

  void update() {
    int reading = analogRead(pin);           // Read the analog value
    sum += reading;                          // Accumulate for average
    count++;
  }

  void compute_average() {
    average = sum / count;                   // Compute the average
    sum = 0;
    count = 0;
    convert();                               // Convert to percentage and bits
  }

  bool has_data() const { return count > 0; }
  int get_percent() const { return percentage; }
  int get_bits() const { return bits; }

private:
  int pin;
  float Vref;
  long sum = 0;
  int count = 0;
  int average = 0;
  int percentage = 0;
  int bits = 0;

  void convert() {
    percentage = map16(average, 900, 1023, 0, 100); // Convert to percentage
    bits = map16(average, 900, 1023, 0, 82);        // Convert to graphical width
  }

  int map16(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
};

// Main class to control the system
class SystemController {
public:
  SystemController(OledDisplay &disp, BatteryMonitor &batt, int limit, int s1, int s2)
    : display(disp), battery(batt),
      limit_switch(limit), switch_1(s1), switch_2(s2) {}

  void begin() {
    pinMode(limit_switch, INPUT_PULLUP);      // Limit switch
    pinMode(switch_1, INPUT_PULLUP);          // Switch 1
    pinMode(switch_2, INPUT_PULLUP);          // Switch 2

    Wire.begin();                            // Initialize I2C
    display.begin();                         // Initialize OLED
    battery.begin();                         // Initialize battery monitor

    battery.update();                        // First sample
    display.show_battery(battery.get_bits(), battery.get_percent());
    wait_for_limit_release();                   // Wait for limit switch release

    start_time = millis();                    // Store initial time
    last_read_time = millis();
  }

  void loop() {
    unsigned long currentTime = millis();

    if (currentTime - start_time >= 6500) {   // Update display every 6.5 s
      if (battery.hasData()) {
        battery.compute_average();
        display.show_battery(battery.get_bits(), battery.get_percent());
      }
      start_time = currentTime;
      last_read_time = currentTime;
    }
    else if (currentTime - last_read_time >= 3000) { // Read battery every 3 s
      battery.update();
      Serial.println("Battery reading...");
      last_read_time = currentTime;
    }
  }

private:
  OledDisplay &display;
  BatteryMonitor &battery;
  int limit_switch, switch_1, switch_2;
  unsigned long start_time, last_read_time;

  void wait_for_limit_release() {
    bool active = true;
    while (active) {
      Serial.println("Limit switch active"); // Print status to serial
      display.show_field_status(digitalRead(switch_1), digitalRead(switch_2));
      active = digitalRead(limit_switch);     // Check if still active
    }
    Serial.println("Limit switch released");
  }
};

// Object creation
OledDisplay oled_disp(128, 64, &Wire, 4);
BatteryMonitor battery_mon(A3, 1.5);
SystemController system_controller(oled_disp, battery_mon, 2, 9, 10);

void setup() {
  Serial.begin(9600);                        // Initialize serial
  system_controller.begin();                 // Initialize the system
}

void loop() {
  system_controller.loop();                  // Run main loop
}