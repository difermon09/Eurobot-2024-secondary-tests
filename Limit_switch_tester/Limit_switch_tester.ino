#define LIMIT_SWITCH 3

void setup() {
  Serial.begin(9600);
  pinMode(LIMIT_SWITCH, INPUT_PULLUP);

  while (digitalRead(LIMIT_SWITCH))
    Serial.println("Waiting to start");
  
  Serial.println("Start!");
}

void loop() {

}
