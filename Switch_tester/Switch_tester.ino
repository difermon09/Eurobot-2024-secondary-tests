#define YELLOW 7
#define BLUE 8
#define LED1 9
#define LED2 10

void setup() {
  Serial.begin(9600);

  pinMode(YELLOW, INPUT_PULLUP);
  pinMode(BLUE, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  if (digitalRead(YELLOW))
    Serial.println("YELLOW 1");

  else if (digitalRead(BLUE))
    Serial.println("BLUE");

  else
    Serial.println("NOTHING");
  
  delay(500);
}
