void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), sensor_a, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), sensor_b, CHANGE);
}


unsigned long LastPulseTimeA = 0;
unsigned long LastPulseTimeB = 0;

void loop() {
  digitalWrite(4, HIGH);
  delay(5);
  digitalWrite(4, LOW);
  delay(200);
  Serial.print("SA: ");
  Serial.print(LastPulseTimeA);
  Serial.print("\tSB: ");
  Serial.println(LastPulseTimeB);
}


void sensor_a() {
  static unsigned long startTimeA;
  if (digitalRead(2))
      startTimeA = micros();
  else
      LastPulseTimeA = micros() - startTimeA;
}

void sensor_b() {
  static unsigned long startTimeB;
  if (digitalRead(3))
      startTimeB = micros();
  else
      LastPulseTimeB = micros() - startTimeB;
}
