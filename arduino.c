#include <Servo.h>

Servo servo_1;
Servo servo_2;

// loop delay
int delay_n    = 500;

// arduino pins
int pin_servo1  = 6;
int pin_servo2  = 7;
int pin_off     = 8;
int pin_action  = 9;

// servo positions
int pos        = 0;
int pos_off    = 20;
int pos_on     = 40;
int pos_attack = 70;

// button vars
bool button_action_pressed = false;
bool button_off_pressed    = false;

// possible states
int state        = -1;
int STATE_OFF    = 0;
int STATE_ON     = 1;
int STATE_ATTACK = 2;


void set_pos_off() {
  if ( state == STATE_OFF ) {
    exit; 
  }
  servo_1.write(pos_off);
  servo_2.write(pos_off);
  delay(delay_n * 3);
  state = STATE_OFF;
}

void set_pos_on() {
  if ( state == STATE_ON ) {
    exit; 
  }
  servo_1.write(pos_on);
  servo_2.write(pos_on);
  delay(delay_n);
  state = STATE_ON;
}

void set_pos_attack() {
  if ( state == STATE_ATTACK ) {
    exit; 
  }
  servo_1.write(pos_attack);
  servo_2.write(pos_attack);
  delay(delay_n);
  state = STATE_ATTACK;
}

void setup() {
  servo_1.writeMicroseconds(1111);
  servo_2.writeMicroseconds(1111);

  
  servo_1.attach(pin_servo1);
  servo_2.attach(pin_servo2);
  
  delay(delay_n * 2);
  set_pos_off();
  pinMode(pin_action, INPUT);
  pinMode(pin_off,    INPUT);
}




void loop() {
  button_action_pressed = digitalRead(pin_action);
  button_off_pressed    = digitalRead(pin_off);
 
  if ( button_off_pressed ) {
    
      set_pos_off();
      
  } else {
    
      if ( button_action_pressed ) {
        
          if ( state == STATE_OFF ) {
             set_pos_on();
          } else {
             set_pos_attack();
          }
          
      } else {
        
          if ( state == STATE_ATTACK ) {
            set_pos_on();
          }
          
      }
      
  }
  delay(delay_n / 2);
}
