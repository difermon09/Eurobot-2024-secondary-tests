#include <Servo.h>
#define SERVO_PIN 5
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}

void loop() {
  servo.write(0);
  Serial.println("0");
  delay(1000);

  servo.write(90);
  Serial.println("90");
  delay(1000);
}
