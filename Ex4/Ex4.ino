int ledPin = 13; // Pin LED is connected to
int piezoBuzzerPin = 10; // Pin Piezo Buzzer is connected to
int pirSensorPin = 9; // PIN PIR Sensor is connected to
float sinVal;
int toneVal;
int motionDetected = LOW; // Start MotionDetected as low (No motiondetected)
void setup() {
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(pirSensorPin, INPUT); // declare the PIR sensor as input
  pinMode(piezoBuzzerPin, OUTPUT); // declare buzzer as output
  Serial.begin(9600); // Set serial out if we want debugging
  delay(5000); // Allow time for the PIR Sensor to calibrate
}
void loop() {
  motionDetected = digitalRead(pirSensorPin); // READ the PIR sensor
  if (motionDetected == HIGH) {
    Serial.println("motion detected!");
    digitalWrite(ledPin, HIGH);
    for (int x = 0; x < 180; x++) {
      // convert degrees to radians then obtain sin value
      sinVal = (sin(x * (3.1412 / 180)));
      // generate a frequency from the sin value
      toneVal = 1000 + (int(sinVal * 2000));
      tone(piezoBuzzerPin, toneVal);
      delay(1);
    }
  }
  else {
    Serial.println("NO motion!"); // NO motion detected
    digitalWrite(ledPin, LOW);
    noTone(piezoBuzzerPin);
    delay(200);
  }
}
