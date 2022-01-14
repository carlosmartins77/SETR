// Definir os pinos para os diferentes componentes
int pirSensor = 9;
int buzzer = 10;
int ledPin = 13;
int buttonPin = 6;

int status = 1;
int buttonStatus = LOW;
int alarmStatus = 0;

int LED1_state = LOW; // Definir o estado do led no inicio do programa para LOW
int BUZZER_state = LOW; // Definir o estado do buzzer  no inicio do programa para LOW
unsigned long ledTime = millis(); // Guardar o tempo da ultima vez que o led piscou
unsigned long buzzerTime = millis(); // Guardar o tempo da ultima vez que o buzzer emitiu um sinal sonoro
unsigned long alarmTime = 0;

long intervalLed = 300; //Piscar o led a cada 300ms
long intervalBuzzer = 400; // Sinal sonoro a cada 400ms

void setup() {
  Serial.begin(9600);
  pinMode(pirSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {

  unsigned long currentTime = millis();
  alarmTime = millis();
  Serial.println(alarmTime);

  buttonStatus = digitalRead(buttonPin);
  verifica = digitalRead(pirSensor);

  Serial.println("VERIFICA:");
  Serial.println(verifica);

  Serial.println("------");
  Serial.println(status);
  Serial.println(alarmStatus);
  Serial.println(buttonStatus);
  Serial.println("------");

  if (status == 1) {
    if (verifica == HIGH || alarmStatus == 1) {
      Serial.println("entrou");
      Serial.println(alarmStatus);
      //delay(99999999);
      alarmStatus = 1;

      if (currentTime - ledTime > intervalLed) {
        LED1_state = !LED1_state;
        digitalWrite(ledPin, LED1_state);

        ledTime = currentTime;
      }
      if (currentTime - buzzerTime > intervalBuzzer) {
        tone(buzzer, 1000, 100);
        delay(200);
        tone(buzzer, 800, 200);
        noTone(buzzer);

        Serial.println("WIWIWIWWIWIWI");

        buzzerTime = currentTime;
      }

    }
  }

  if (buttonStatus == HIGH) { // Se o botão tiver sido carregado
    Serial.println("button");
    Serial.println(status);
    status = !status;

    if (status == 0) {
      alarmStatus = !alarmStatus;
    } else
      alarmStatus = 0;
    digitalWrite(buzzer, LOW);
  }
  // Se tiverem passados 10segundos e o botao clicado tiver sido clicado
  if (alarmTime >= 10000 || buttonStatus == HIGH) { 
    digitalWrite(ledPin, LOW); // Desliga o led
    noTone(buzzer); // Desliga o buzzer
  }

  //Delay 50ms before next reading.
  delay(50);
}
