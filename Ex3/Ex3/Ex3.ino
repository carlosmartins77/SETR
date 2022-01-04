#include <IRremote.h>
#include <Servo.h>

#define subir 34935 //Botao 0
#define descer 8415 //Botao 1
#define parar 41055 //Botao 2

int receiver_pin = 11;
Servo motor;
int pos;
int buttonPin = 3;
int state = 0;
unsigned long lastInterrupt;

IRrecv receiver(receiver_pin);
decode_results output;


void setup()
{
  Serial.begin(9600);
  receiver.enableIRIn();
  motor.attach(9);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), suspender, HIGH);
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
      
        for (pos = 90; pos <= 180; pos += 1)
        {
            motor.write(pos);
            delay(15);
        }
        break;
      
      case descer:
        for (pos = 180; pos >= 90; pos -= 1)
        {
          motor.write(pos);
          delay(15);
        }
        break;
      
      case parar:
        //motor.detach();
    //attachInterrupt(receiver_pin, teste, CHANGE);
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
