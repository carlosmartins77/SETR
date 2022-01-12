#include <IRremote.h>
#include <Servo.h>

#define subir 34935 //Botao 0
#define descer 8415 //Botao 1

int receiver_pin = 11; // IR Sensor
Servo motor; // Servo
int pos; // Posiçao para o SERVO (Usada para definir a velocidade do servo)

int buttonPin = 3; // Botao suspender movimento
unsigned long lastInterrupt;
int state = 0;

IRrecv receiver(receiver_pin);
decode_results output;


void setup()
{
  Serial.begin(9600);


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

        subirBarra();
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

  //motor.attach(9);
}

void subirBarra()
{
  for (pos = 0; pos <= 180; pos += 1)
  {
    motor.write(pos);
    delay(15);
  }
}


void descerBarra()
{

  for (pos = 180; pos >= 0; pos -= 1)
  {
    motor.write(pos);
    delay(15);
  }
  
}
