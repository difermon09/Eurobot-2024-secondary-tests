// Program that reads the state of two buttons (YELLOW and BLUE) and prints which one is pressed.
// If no button is active, prints "NOTHING".

#define YELLOW 7   // Pin for the yellow button
#define BLUE 8     // Pin for the blue button

void setup() {
  Serial.begin(9600);                // Initialize serial communication

  pinMode(YELLOW, INPUT_PULLUP);     // Yellow button with internal pull-up
  pinMode(BLUE, INPUT_PULLUP);       // Blue button with internal pull-up
}

void loop() {
  if (digitalRead(YELLOW))           // If the yellow button is pressed
    Serial.println("YELLOW");      // Print corresponding message

  else if (digitalRead(BLUE))        // If the blue button is pressed
    Serial.println("BLUE");        // Print corresponding message

  else
    Serial.println("NOTHING");     // No button pressed

  delay(500);                        // Wait before next reading
