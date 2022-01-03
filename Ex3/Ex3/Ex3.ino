#include <IRremote.h>
#include <Servo.h>

#define subir 34935 //Botao 0
#define descer 8415 //Botao 1
#define parar 41055 //Botao 2

int receiver_pin = 11;
Servo motor;

IRrecv receiver(receiver_pin);
decode_results output;
int pos;

void setup()
{
  Serial.begin(9600);
  receiver.enableIRIn();
  motor.attach(9);
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
        for (pos = 90; pos <= 180 || value == 41055; pos += 1)
        {
          motor.write(pos);
          delay(15);
        }
        break;
      case descer:
        descerServo(motor);
        delay(15);
        break;
      case parar:
        motor.detach();
        break;
    }

  }

}

void subirServo(Servo motor)
{
  int pos;

  for (pos = 90; pos <= 180; pos += 1)
  {
    motor.write(pos);
    delay(15);
  }
}

void descerServo(Servo motor)
{
  int pos;

  for (pos = 180; pos >= 90; pos -= 1)
  {
    motor.write(pos);
    delay(15);
  }
}
