// Simple program to test a DC motor using PWM.
// Prints the PWM value to Serial and ramps motor power up and down.

#define DC 9                  // PWM pin connected to the motor (e.g., transistor/driver)

void setup() {
  Serial.begin(9600);        // Initialize serial communication at 9600 bps
  pinMode(DC, OUTPUT);       // Configure the motor pin as PWM output
}

void loop() {
  // RAMP UP: increase PWM from 0 to 255 in steps
  for (float i = 0; i <= 255; i += 25.5) {
    analogWrite(DC, i);     // Apply PWM value to the motor
    Serial.print("PWM: ");
    Serial.println(i);      // Print current value to serial monitor
    delay(1000);            // Hold each step 1 second to observe change
  }

  // RAMP DOWN: decrease PWM from 255 to 0 in steps
  for (float i = 255; i >= 0; i -= 25.5) {
    analogWrite(DC, i);
    Serial.print("PWM: ");
    Serial.println(i);
    delay(1000);
  }
}
