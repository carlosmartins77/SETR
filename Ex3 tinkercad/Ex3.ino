#include <IRremote.h>
#include <Servo.h>

#define subir 12495 //Botao 0
#define descer 2295 //Botao 1


int receiver_pin = 11; // IR Sensor
Servo motor; // Servo
int pos; // Posiçao para o SERVO (Usada para definir a velocidade do servo)

int buttonPin = 3; // Botao suspender movimento
unsigned long lastInterrupt;
int state = 0;

/* Sensor distancia*/
int trigPin = 8;
int echoPin = 7;
long duration, distance; // Duration used to calculate distance
/* ---- */

IRrecv receiver(receiver_pin);
decode_results output;

unsigned long timeStart;
unsigned long timeEnd;

void setup()
{
  Serial.begin(9600);
  
  /* Sensor distancia*/
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  /* ---- */
  
  /* Infravermelhos */
  receiver.enableIRIn();
  /* ---- */
  
  motor.attach(9); //Ligar o SERVO à porta 9
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), suspender, FALLING);
}

void loop()
{ 
  if (receiver.decode(&output))
  {
    unsigned int value = output.value;
    Serial.println(value);
    receiver.resume();

    switch (value)
    {
        receiver.resume();

      case subir:
      
        subirBarra(-1);
        break;
      
      case descer:
        descerBarra();
        break;
      
    }

  }
}

void suspender() {
   
  state = !state;
    Serial.println(state);
    if (state == 1)
        motor.detach();
    else
        motor.attach(9);

}

void subirBarra(int position)
{
  if (pos != 180) {
    
    if (position >= 0)
      pos = position;
    else
      pos = 0;
    
    for (; pos < 180; pos += 1)
    {
      motor.write(pos);
      delay(15);
    }
  }
    
}
  

void descerBarra()
{
  if (pos != 0) {
    for (pos = 180; pos > 0; pos -= 1)
    {
      digitalWrite(trigPin, HIGH); //Enviar onde ultrassonica
      delayMicroseconds(10); //Durante 10ms
      digitalWrite(trigPin, LOW); //Para de enviar onda
      duration = pulseIn(echoPin, HIGH);
      distance = (duration/58.2)*2;
      
      if(distance > 200) {
          motor.write(pos);
          delay(25);
      }
      else if(distance <= 200){
        
          subirBarra(pos);
          break;         
      }    
    }
  }
}
