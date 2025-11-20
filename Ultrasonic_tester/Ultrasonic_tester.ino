// Ultrasonic sensor only
// Pins and simple measurement using pulseIn

const int trig_pin = 8;
const int echo_pin = 10;

float distance_cm = 0.0;

// Measure distance in centimeters (simple version)
float measure_distance_cm() {

  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);


  unsigned long duration = pulseIn(echo_pin, HIGH);

  float distance = duration * 0.0172;
  return distance;
}

void setup() {
  Serial.begin(9600);

  // Configure ultrasonic pins
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  distance_cm = measure_distance_cm();
  Serial.print("Distance (cm): ");
  Serial.println(distance_cm);
  delay(500);
}
