// Definir os pinos para os diferentes componentes
int pirSensor = 9;
int buzzer = 10;
int ledPin = 13;
int buttonPin = 6;

// Estado do sistema, se estiver 1 significa que está ligado e o alarme está ativo
// se tiver 0 o sistema está desligado e o alarme está desativado
int status = 1; 
// Estado do botão, se tiver HIGH é porque foi pressionado para interromper o alarme
int buttonStatus = LOW;
// Estado do alarme, se estiver 1 é porque o alarme foi disparado
int alarmStatus = 0;
// Estado do pir, o valor é HIGH quando deteta movimento
int verifica;

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

  // Se o alarme estiver ativo e for detetado movimento
  // o alarme dispara
  if (status == 1) {
    if (verifica == HIGH || alarmStatus == 1) {
      alarmStatus = 1;

      // utilizado no multitasking, verifica se esta na fatia de tempo do led para piscar
      if (currentTime - ledTime > intervalLed) {
        LED1_state = !LED1_state;
        digitalWrite(ledPin, LED1_state);

        ledTime = currentTime;
      }
      // utilizado no multitasking, verifica se esta na fatia de tempo do buzzer para ativar
      if (currentTime - buzzerTime > intervalBuzzer) {
        tone(buzzer, 1000, 100);
        delay(200);
        tone(buzzer, 800, 200);
        noTone(buzzer);

        buzzerTime = currentTime;
      }

    }
  }

  // Se o botão for pressionado desliga o alarme
  if (buttonStatus == HIGH) {
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

  delay(50);
}
