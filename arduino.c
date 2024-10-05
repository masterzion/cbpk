#include <Servo.h>

Servo servo_1;

// loop delay
int delay_n    = 300;

// arduino pins
int pin_servo  = 7;
int pin_off    = 8;
int pin_action = 9;

// servo positions
int pos        = 0;
int pos_off    = 20;
int pos_on     = 40;
int pos_attack = 60;

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
  delay(delay_n * 5);
  state = STATE_OFF;
}

void set_pos_on() {
  if ( state == STATE_ON ) {
    exit; 
  }
  servo_1.write(pos_on);
  delay(delay_n);
  state = STATE_ON;
}

void set_pos_attack() {
  if ( state == STATE_ATTACK ) {
    exit; 
  }
  servo_1.write(pos_attack);
  delay(delay_n);
  state = STATE_ATTACK;
}

/*
servo_1.writeMicroseconds(1111);  // Moves the servo to approximately 20 degrees
servo_1.writeMicroseconds(1222);  // Moves the servo to approximately 40 degrees
servo_1.writeMicroseconds(1278);  // Moves the servo to approximately 50 degrees
*/


void setup() {
  servo_1.writeMicroseconds(1111);
  servo_1.attach(pin_servo);
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
