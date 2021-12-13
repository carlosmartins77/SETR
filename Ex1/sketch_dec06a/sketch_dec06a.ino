int ldrPin = A0;    
int ledPin = 5;  
int ldrValue = 0;

void setup() {
  Serial.begin(9600);    
  pinMode(ledPin, OUTPUT);
}

void loop() {
  ldrValue = analogRead(ldrPin); 
  Serial.print("Valor entrada LDR:");
  Serial.println(ldrValue);
  if (200 > ldrValue) 
  {
    digitalWrite(ledPin, 0);
    Serial.println("1");
  }
  else if (ldrValue >= 200 && ldrValue < 500) 
  {
    digitalWrite(ledPin, 64);
    Serial.println("2");
  }
  else if(ldrValue >= 500 && ldrValue < 800)
  {
    digitalWrite(ledPin, 128);
    Serial.println("3");
  }
  else if(ldrValue > 800)
  {
    digitalWrite(ledPin, 255);
    Serial.println("4");
  }
}
