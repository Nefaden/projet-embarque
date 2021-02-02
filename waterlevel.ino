int sensorPin = A0;
int ledPin = 13;

int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop()  {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  digitalWrite(ledPin, LOW);

// Sensor value is between 400 and 200 (even dried, still displaying 200)
  if (sensorValue < 200) {
    digitalWrite(ledPin, HIGH);
  }
}
