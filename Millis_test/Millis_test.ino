int led_1 = 13;
int led_2 = 9;
int previous_time_1 = 0;
int previous_time_2 = 0;
int current_time = 0;


void setup() {
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  current_time = millis();
  if (current_time - previous_time_1 == 1000) {
    if (digitalRead(led_1) == LOW) {
      digitalWrite(led_1, HIGH);
    } else {
      digitalWrite(led_1, LOW);
    }
    previous_time_1 = current_time;
  }
  if (current_time - previous_time_2 == 2000) {
    if (digitalRead(led_2) == LOW) {
      digitalWrite(led_2, HIGH);
    } else {
      digitalWrite(led_2, LOW);
    }
    previous_time_2 = current_time;
  }
}
