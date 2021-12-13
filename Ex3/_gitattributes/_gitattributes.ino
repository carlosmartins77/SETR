#include <IRremote.h>
#include <Servo.h>

#define subir 34935 //Botao 0
#define descer 8415 //Botao 1
#define parar 41055 //Botao 2

int receiver_pin = 11;
Servo motor;

IRrecv receiver(receiver_pin);
decode_results output;

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

    switch(value)
    {
      case subir: 
        motor.write(90);
        delay(15);
        break;
      case descer:
        motor.write(0);
        delay(15);
        break;
       case parar:
        motor.detach();
        break;
    }
    
    
  }
    
}
