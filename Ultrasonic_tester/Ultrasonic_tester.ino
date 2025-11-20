// Simple ultrasonic sensor measurement using pulseIn().
// Sets up TRIG and ECHO pins and calculates distance in centimeters.

const int trig_pin = 8;   // Pin for TRIG signal
const int echo_pin = 10;  // Pin for ECHO signal

float distance_cm = 0.0;  // Variable to store measured distance

// Function to measure distance in cm
float measure_distance_cm() {
  digitalWrite(trig_pin, LOW);          // Ensure TRIG is LOW before starting
  delayMicroseconds(2);                 // Short wait

  digitalWrite(trig_pin, HIGH);         // Trigger for 10 µs
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);          // Return TRIG to LOW

  unsigned long duration = pulseIn(echo_pin, HIGH); // Measure pulse duration HIGH

  float distance = duration * 0.0172;  // Convert duration to cm (speed of sound)
  return distance;                      // Return calculated distance
}

void setup() {
  Serial.begin(9600);                   // Initialize serial communication

  pinMode(trig_pin, OUTPUT);            // Configure TRIG as output
  pinMode(echo_pin, INPUT);             // Configure ECHO as input
}

void loop() {
  distance_cm = measure_distance_cm();  // Call function to get distance
  Serial.print("Distance (cm): ");    // Print label
  Serial.println(distance_cm);          // Print measured value
  delay(500);                           // Wait before next reading
}