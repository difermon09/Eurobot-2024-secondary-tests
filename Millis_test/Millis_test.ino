// Program that controls two LEDs at two different frequencies without blocking execution.

const int led_1 = 13;                  // Pin for LED 1
const int led_2 = 9;                   // Pin for LED 2
int previous_time_1 = 0;         // Previous time for LED 1
int previous_time_2 = 0;         // Previous time for LED 2
int current_time = 0;            // Current time

void setup() {
  pinMode(led_1, OUTPUT);        // Configure LED 1 as output
  pinMode(led_2, OUTPUT);        // Configure LED 2 as output
  Serial.begin(9600);            // Initialize serial communication
}

void loop() {
  current_time = millis();       // Read current time

  // Check if 1 second has passed for LED 1
  if (current_time - previous_time_1 == 1000) {
    if (digitalRead(led_1) == LOW) {
      digitalWrite(led_1, HIGH); // Turn LED 1 on
    } else {
      digitalWrite(led_1, LOW);  // Turn LED 1 off
    }
    previous_time_1 = current_time; // Update previous time
  }

  // Check if 2 seconds have passed for LED 2
  if (current_time - previous_time_2 == 2000) {
    if (digitalRead(led_2) == LOW) {
      digitalWrite(led_2, HIGH); // Turn LED 2 on
    } else {
      digitalWrite(led_2, LOW);  // Turn LED 2 off
    }
    previous_time_2 = current_time; // Update previous time
  }
