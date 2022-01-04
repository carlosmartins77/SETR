// defines pins numbers
int trigPin = 8;
int echoPin = 7;
int buzzer = 10;
int ledPin = 13;
int buttonPin = 6;
int status = 1;
int buttonStatus = LOW;
int alarmStatus = 0;

long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(ledPin, OUTPUT); 
 pinMode(buttonPin, INPUT);

}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 buttonStatus = digitalRead(buttonPin);
 
 Serial.println("------");
 Serial.println(status);
 Serial.println(alarmStatus);
 Serial.println("------");
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigPin, LOW);

 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
  if (status == 1) {
   if (distance <= 50 && distance > 2 || alarmStatus == 1){
     Serial.println("entrou");
     Serial.println(distance);
     Serial.println(alarmStatus);
     //delay(99999999);
     alarmStatus = 1;
     digitalWrite(ledPin, HIGH); 
     digitalWrite(buzzer, HIGH);  
   }
  }
 //else if (distance > 50 && alarmStatus == 0){
 //  digitalWrite(ledPin, LOW);
 //  digitalWrite(buzzer, LOW);
 //}
 
 if (buttonStatus == HIGH) {
    Serial.println("button");
     Serial.println(status);
    status = !status;
    Serial.println(status);
    delay(200);
    if (status == 0) {
      alarmStatus = !alarmStatus;
    }
    else
      alarmStatus = 0;
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzer, LOW);
 }
  
 
 //Delay 50ms before next reading.
 delay(50);
}
