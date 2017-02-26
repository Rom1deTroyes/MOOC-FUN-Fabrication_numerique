const byte LEDV = 10;
const byte LEDO = 11;
const byte LEDR = 12;

const byte LEDPV = 8;
const byte LEDPR = 9;

const byte LEDI = 13;

const byte BUTTON = 2;

volatile boolean etat = LOW ;

// Interrupt Service Routine (ISR)
void switchPressed ()
{
  if (digitalRead (BUTTON) == HIGH)
    etat = HIGH;
  else
    etat = LOW;
}  // end of switchPressed

void setup ()
{
  pinMode (LEDV, OUTPUT);  // so we can update the LED
  pinMode (LEDO, OUTPUT);  // so we can update the LED
  pinMode (LEDR, OUTPUT);  // so we can update the LED
  pinMode (LEDPV, OUTPUT);  // so we can update the LED
  pinMode (LEDPR, OUTPUT);  // so we can update the LED
  pinMode (LEDI, OUTPUT);  // so we can update the LED
  digitalWrite (BUTTON, HIGH);  // internal pull-up resistor
  attachInterrupt (INT0, switchPressed, CHANGE);  // attach interrupt handler
}  // end of setup

void loop ()
{
  if(!etat){
    digitalWrite (LEDV, HIGH);
    digitalWrite (LEDO, LOW);
    digitalWrite (LEDR, LOW);

  } 
  else {
    delay(1000);
    digitalWrite (LEDV, LOW);
    digitalWrite (LEDO, HIGH);
    delay(1000);
    digitalWrite (LEDO, LOW);
    digitalWrite (LEDR, HIGH);
    delay(1000);
    digitalWrite (LEDPV, HIGH);
    digitalWrite (LEDPR, LOW);
    delay(5000);
    digitalWrite (LEDPR, HIGH);
    digitalWrite (LEDPV, LOW);
    delay(1000);
  }

  digitalWrite (LEDI, etat);
} 


