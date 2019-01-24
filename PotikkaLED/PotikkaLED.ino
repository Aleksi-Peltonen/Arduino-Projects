
#define LED 3
#define KNOB 0

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED, 0);
  // Read the value of the potentiometer knob
  int knobValue = analogRead(KNOB);

  // Map the potentiometer value to 1-255
  int speedy = map(knobValue, 0, 1024, 40,500 );

  // Output the respective value to the LED
  delay(speedy);
  digitalWrite(LED, 1);
  delay(speedy);
  Serial.println(speedy);
}
