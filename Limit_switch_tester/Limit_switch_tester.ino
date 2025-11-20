// Simple program to test a limit switch.

#define LIMIT_SWITCH 3          // Pin where the limit switch is connected

void setup() {
  Serial.begin(9600);         // Initialize serial communication
  pinMode(LIMIT_SWITCH, INPUT_PULLUP); // Use internal pull-up resistor

  // Wait until the limit switch is activated (reads LOW when pressed)
  while (digitalRead(LIMIT_SWITCH))
    Serial.println("Waiting to start");
  
  Serial.println("Start!");   // Reached when the switch is activated
}

void loop() {
  // Empty: main behaviour is performed in setup for a simple test
}
