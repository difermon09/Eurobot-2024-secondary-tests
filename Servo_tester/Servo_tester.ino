// Control a servo using the Servo library and print current position to Serial.

#include <Servo.h>
#define SERVO_PIN 5

Servo servo;  // Object to control the servo

void setup() {
  Serial.begin(9600);         // Initialize serial communication
  servo.attach(SERVO_PIN);    // Attach the pin to the servo
}

void loop() {
  servo.write(0);             // Move servo to 0 degrees
  Serial.println("0");      // Print current position
  delay(1000);                // Wait 1 second

  servo.write(90);            // Move servo to 90 degrees
  Serial.println("90");     // Print current position
  delay(1000);                // Wait 1 second
