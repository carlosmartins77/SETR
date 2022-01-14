#include <IRremote.h>
#include <Servo.h>

#define subir 34935 //Botao 0
#define descer 8415 //Botao 1

int receiver_pin = 11; // IR Sensor
Servo motor; // Servo
int pos = 180; // Posiçao para o SERVO (Usada para definir a velocidade do servo)

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

  motor.write(pos);
  motor.attach(9); //Ligar o SERVO à porta 9
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), suspender, FALLING);
}

void loop()
{
  if (receiver.decode(&output))
  {
    unsigned int value = output.value;
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
      motor.write(pos);
      delay(15);
    }
  }
}