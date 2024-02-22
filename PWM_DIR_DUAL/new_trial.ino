/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example shows how to drive 2 motors using the PWM and DIR pins with
 * 2-channel motor driver.
 * 
 * 
 * CONNECTIONS:
 * 
 * Arduino D3  - Motor Driver PWM 1 Input
 * Arduino D4  - Motor Driver DIR 1 Input
 * Arduino D9  - Motor Driver PWM 2 Input
 * Arduino D10 - Motor Driver DIR 2 Input
 * Arduino GND - Motor Driver GND
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

 #include <CytronMotorDriver.h>

// Define motor pins
#define LEFT_MOTOR_PWM 3
#define LEFT_MOTOR_DIR 4
#define RIGHT_MOTOR_PWM 5
#define RIGHT_MOTOR_DIR 6

// Define joystick pins
#define JOYSTICK_X A7
#define JOYSTICK_Y A8

#define thresholdx 30
#define thresholdy 30
#define thresholdstr 30
// Create motor objects
CytronMD motorLeft(PWM_DIR,LEFT_MOTOR_PWM, LEFT_MOTOR_DIR);
CytronMD motorRight(PWM_DIR,RIGHT_MOTOR_PWM, RIGHT_MOTOR_DIR);

void setup() {
  // Set motor control pins as outputs
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
}

void loop() {
  // Read joystick values
  int x = analogRead(JOYSTICK_X);
  int y = analogRead(JOYSTICK_Y);
  x = map(val, 0, 1023, -255, 255);
  y = map(val, 0, 1023, -255, 255);
  Serial.print(x);
  Serial.print("  "); 
  Serial.print(y);
 
   if( (y > thresholdy || (-thresholdy) > y) && (( x < thresholdx && (-thresholdx) < x)) ){    
    motorLeft.setSpeed(y);
    motorRight.setSpeed(y);
    Serial.println("Straight");
  }
  if( (x > thresholdx || (-thresholdx) > x)  && (( y < thresholdy && (-thresholdy) < y))){
    motorLeft.setSpeed((x));
    motorRight.setSpeed(x);
        Serial.println("Rotate");

  }
  if( (x > thresholdx || (-thresholdx) > x)  && (( y > thresholdy ))){
    motorLeft.setSpeed(y+x);
    motorRight.setSpeed(y-x);
        Serial.println("Diagonal Ahead");

  }

  if( (x > thresholdx || (-thresholdx) > x)  && (( y < (-thresholdy) ))){
    motorLeft.setSpeed(y-x);
    motorRight.setSpeed(y+x);
        Serial.println("Diagonal Behind");

  }
    
  if(x <thresholdx && (-thresholdx) < x && y <thresholdx && (-thresholdx) < y){
    motorLeft.setSpeed(0);
    motorRight.setSpeed(0);
    Serial.println("Stop");
    }


}