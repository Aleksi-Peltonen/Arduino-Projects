int blueLed = 4;
char data;

void setup() {
  // put your setup code here, to run once:
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {     //wait here until the data is available
    data = Serial.read();
    Serial.println(data);
  }

  if (data == '1') {
    digitalWrite(blueLed, HIGH);
    Serial.println("Blue LED On");
    data = '4';
  }

  if (data == '2') {
    digitalWrite(blueLed, LOW);
    Serial.println("Blue LED Off");
    data = '4';
  }
  
}
