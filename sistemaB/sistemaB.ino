#include <LiquidCrystal.h>
// componentes
/*  motor (ventoinha)
 *  sensor de temperatura
 *  lcd (a mostrar se a fan esta on/off e a temp)
 *  led vermelho (liga quando está a ventoinha ligada)
 *  led verde (liga quando a temp está estabilizada)
 *  potenciometro (para controlar a luminosidade do lcd)
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int fanPin;
int lcdPin;
int ledCooling = 8; // led vermelho - liga quando está a ventoinha ligada
int ledStabilized = 7; // led verde - liga quando a temperatura está estabilizada
int maxTemp = 25; // temperatura maxima tolerada antes de ligar a ventoinha
int minTemp = 20; // temperatura minima que quando atingida desliga a ventoinha
int tempPin = A1; 
int motorPin = 6;
float temp;


void setup() {
  // put your setup code here, to run once:
  pinMode(fanPin, OUTPUT);
  pinMode(lcdPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.print("Fan: ");
  Serial.print("Fan: ");
  temp_regulator ();
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // temp >25º liga
  // temp <20º desliga
  
  temp = analogRead(tempPin); // le valor do sensor de temperatura
  
  // converte o valor em uma temperatura em ºC
  temp = temp * 5 / 1024;
  temp = (temp - 0.5) * 100;
  
  lcd.setCursor(6, 0);
  lcd.print("Fan: ");
  Serial.print("Fan: ");
  
  temp_regulator ();

  lcd.setCursor(6, 1);
  lcd.print(temp, 1);
  Serial.print("Temp: ");
  Serial.println(temp); 

  delay(500);
    
}

void temp_regulator (){
  if (temp > maxTemp) {
    Serial.println("ON ");
    lcd.print("ON ");
    digitalWrite(ledCooling, HIGH);
    digitalWrite(ledStabilized, LOW);
    digitalWrite(motorPin, HIGH);
  } else if (temp < minTemp) {
    Serial.println("OFF");
    lcd.print("OFF");
    digitalWrite(ledCooling, LOW);
    digitalWrite(ledStabilized, HIGH);
    digitalWrite(motorPin, LOW);
  } else {
    Serial.println("OFF");
    lcd.print("OFF");
    digitalWrite(ledCooling, HIGH);
    digitalWrite(ledStabilized, LOW);
    digitalWrite(motorPin, LOW);
  }
}
