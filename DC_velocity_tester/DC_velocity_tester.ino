#define DC 9

void setup() {
  Serial.begin(9600);
  pinMode(DC,OUTPUT);
}

void loop() {
  // UP
  for (float i = 0; i <= 255; i += 25.5) {
    analogWrite(DC, i);
    Serial.print("PWM: ");
    Serial.println(i);
    delay(1000);
  }

  // DOWN
  for (float i = 255; i >= 0; i -= 25.5) {
    analogWrite(DC, i);
    Serial.print("PWM: ");
    Serial.println(i);
    delay(1000);
  }
}
