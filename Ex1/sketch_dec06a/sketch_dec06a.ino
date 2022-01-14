int ldrPin = A0;    
int ledPin = 5;  
int ldrValue = 0;

void setup() {
  Serial.begin(9600);    
  pinMode(ledPin, OUTPUT);
}

void loop() {
  ldrValue = analogRead(ldrPin);
  if (200 > ldrValue) 
  {
    digitalWrite(ledPin, 0);
  }
  else if (ldrValue >= 200 && ldrValue < 500) 
  {
    digitalWrite(ledPin, 64);
  }
  else if(ldrValue >= 500 && ldrValue < 800)
  {
    digitalWrite(ledPin, 128);
  }
  else if(ldrValue > 800)
  {
    digitalWrite(ledPin, 255);
  }
}
