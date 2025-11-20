#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ============================
// --- OLED Display Class ---
// ============================
class OledDisplay {
public:
  Adafruit_SSD1306 oled;
  
  OledDisplay(uint8_t width, uint8_t height, TwoWire *wire, int8_t rst)
    : oled(width, height, wire, rst) {}

  void begin() {
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.clearDisplay();
    oled.display();
  }

  void showBattery(int bits, int percent) {
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(10, 0);
    oled.setTextSize(1);
    oled.print("Battery Percentage");
    oled.setCursor(117, 1);
    oled.print(":");

    // Battery frame
    oled.drawRect(22, 18, 84, 43, WHITE);
    oled.fillRect(107, 29, 3, 22, WHITE);
    oled.fillRect(23, 19, bits, 42, WHITE);

    // Percentage number
    oled.fillRect(38, 25, 52, 29, BLACK);
    centerText(percent);
    oled.setTextSize(2);
    oled.print(percent);
    oled.print("%");
    oled.display();
  }


  void showFieldStatus(bool s1, bool s2) {
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(10, 50);
    oled.setTextSize(1);

    if (!s1 && !s2) {
      Serial.println("Homologation");
      oled.print("H");
    } else if (s1) {
      Serial.println("Blue");
      oled.print("B");
    } else {
      Serial.println("Yellow");
      oled.print("Y");
    }
    oled.display();
  }

private:
  void centerText(int percent) {
    if (percent < 10)      
      oled.setCursor(55, 32);
    else if (percent == 100) 
      oled.setCursor(42, 32);
    else                   
      oled.setCursor(49, 32);
  }
};

// ============================
// --- Battery Monitor Class ---
// ============================
class BatteryMonitor {
public:
  BatteryMonitor(int pin, float refV) : pin(pin), Vref(refV) {}

  void begin() {
    pinMode(pin, INPUT);
    analogReference(EXTERNAL);
  }

  void update() {
    int reading = analogRead(pin);
    sum += reading;
    count++;
  }

  void computeAverage() {
    average = sum / count;
    sum = 0;
    count = 0;
    convert();
  }
  
  bool hasData() const { return count > 0; }
  int getPercent() const { return percentage; }
  int getBits() const { return bits; }

private:
  int pin;
  float Vref;
  long sum = 0;
  int count = 0;
  int average = 0;
  int percentage = 0;
  int bits = 0;
  // float voltage = 0;

  void convert() {
    // voltage = avg_battery_reading * voltageRef / 1023;
    percentage = map16(average, 900, 1023, 0, 100);
    bits = map16(average, 900, 1023, 0, 82);
  }

  int map16(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
};

// ============================
// --- System Controller ---
// ============================
class SystemController {
public:
  SystemController(OledDisplay &disp, BatteryMonitor &batt, int limit, int s1, int s2)
    : display(disp), battery(batt),
      limitSwitch(limit), switch1(s1), switch2(s2) {}

  void begin() {
    pinMode(limitSwitch, INPUT_PULLUP);
    pinMode(switch1, INPUT_PULLUP);
    pinMode(switch2, INPUT_PULLUP);

    Wire.begin();
    display.begin();
    battery.begin();

    battery.update();
    display.showBattery(battery.getBits(), battery.getPercent());
    waitForLimitRelease();

    startTime = millis();
    lastReadTime = millis();
  }

  void loop() {
    unsigned long currentTime = millis();

    // Every 6.5 seconds, compute and display
    if (currentTime - startTime >= 6500) {
      if (battery.hasData()) {
        battery.computeAverage();
        display.showBattery(battery.getBits(), battery.getPercent());
      }
      startTime = currentTime;
      lastReadTime = currentTime;
    }

    // Every 3 seconds, read battery
    else if (currentTime - lastReadTime >= 3000) {
      battery.update();
      Serial.println("Battery reading...");
      lastReadTime = currentTime;
    }
  }

private:
  OledDisplay &display;
  BatteryMonitor &battery;
  int limitSwitch, switch1, switch2;
  unsigned long startTime, lastReadTime;

  void waitForLimitRelease() {
    bool active = true;
    while (active) {
      Serial.println("Limit switch active");
      display.showFieldStatus(digitalRead(switch1), digitalRead(switch2));
      active = digitalRead(limitSwitch);
    }
    Serial.println("Limit switch released");
  }
};


OledDisplay oledDisp(128, 64, &Wire, 4);
BatteryMonitor batteryMon(A3, 1.5);
SystemController systemController(oledDisp, batteryMon, 2, 9, 10);

void setup() {
  Serial.begin(9600);
  systemController.begin();
}

void loop() {
  systemController.loop();
}

