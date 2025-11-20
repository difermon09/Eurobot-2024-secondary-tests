#define INT1 8
#define INT2 7
#define ENA 5

void setup() {
  Serial.begin(9600);
  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  velocity_tester();

  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  velocity_tester();

  digitalWrite(INT1, LOW);
  digitalWrite(INT2, LOW);
  Serial.println("Stop");
  delay(1000);
}

void velocity_tester(){
  // UP
  for (uint8_t i = 0; i <= 255; i += 15) {
    analogWrite(ENA, i);
    Serial.print("PWM: ");
    Serial.println(i);
    delay(500);
  }
  delay(900);

  // DOWN
  for (uint8_t i = 255; i >= 0; i -= 15) {
    analogWrite(ENA, i);
    Serial.print("PWM: ");
    Serial.println(i);
    delay(500);
  }
  delay(900);
}