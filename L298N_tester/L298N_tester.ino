// Program to test an L298N driver and adjust motor speed with PWM.
#define INT1 8   // IN1 pin of L298N (direction)
#define INT2 7   // IN2 pin of L298N (direction)
#define ENA 5    // ENA (enable) pin connected to PWM to control speed

void setup() {
  Serial.begin(9600);        // Initialize serial communication
  pinMode(INT1, OUTPUT);     // Configure direction pins as outputs
  pinMode(INT2, OUTPUT);
  pinMode(ENA, OUTPUT);      // Configure ENA as PWM output
}

void loop() {
  // Rotate in one direction
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  velocity_tester();         // Ramp PWM up and down

  // Rotate in the opposite direction
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  velocity_tester();

  // Stop
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, LOW);
  Serial.println("Stop");
  delay(1000);
}

void velocity_tester(){
  // RAMP UP: gradually increase PWM to observe motor response
  for (uint8_t i = 0; i <= 255; i += 15) {
    analogWrite(ENA, i);     // Apply PWM to ENA
    Serial.print("PWM: ");
    Serial.println(i);
    delay(500);
  }
  delay(900);

  // RAMP DOWN: decrease PWM
  for (uint8_t i = 255; i >= 0; i -= 15) {
    analogWrite(ENA, i);
    Serial.print("PWM: ");
    Serial.println(i);
    delay(500);
  }
  delay(900);
}