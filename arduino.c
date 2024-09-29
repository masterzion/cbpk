#include <Servo.h>

Servo servo_1;

int pin_servo  = 13;
int pin_action = 10;
int pin_off = 9;

int delay_n    = 300;

int pos        = 0;
int pos_off    = 0;
int pos_rest   = 45;
int pos_attack = 90;

bool button_action  = false;
bool button_off     = false;

void setup() {
  servo_1.attach(pin_servo);
  pinMode(pin_action, INPUT);
  pinMode(pin_off,    INPUT);
}


void loop() {

  button_action = (digitalRead(pin_action) == HIGH);
  button_off    = (digitalRead(pin_off) == HIGH);

  if ( button_off ) {
    pos = pos_off;
  } else {
    if ( button_action ) {
      if (pos == pos_off) {
        pos = pos_rest;
        servo_1.write(pos);
        delay(delay_n * 1.5);
      } else {
        pos = pos_attack;
      }
    } else {
      if (pos == pos_attack) {
        pos = pos_rest;
        delay(delay_n);
      }
    }
  }


  delay(delay_n);
  servo_1.write(pos);
}
