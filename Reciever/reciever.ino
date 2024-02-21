#include <CytronMotorDriver.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// Define motor pins
#define LEFT_MOTOR_PWM 3
#define LEFT_MOTOR_DIR 4
#define RIGHT_MOTOR_PWM 5
#define RIGHT_MOTOR_DIR 6

// Define joystick pins


#define thresholdx 10
#define thresholdy 10
#define thresholdstr 10
// Create motor objects
CytronMD motorLeft(PWM_DIR,LEFT_MOTOR_PWM, LEFT_MOTOR_DIR);
CytronMD motorRight(PWM_DIR,RIGHT_MOTOR_PWM, RIGHT_MOTOR_DIR);

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "12359";
char receivedData[32] = "";
int  x, y;

void setup() {
  Serial.begin(9600);
  // Set motor control pins as outputs
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  Serial.println(-(thresholdy));
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // Read joystick values
  if (radio.available()) {   // If the NRF240L01 module received data
    radio.read(&receivedData, sizeof(receivedData)); // Read the data and put it into character array
    x = atoi(&receivedData[0]);
    Serial.print(x);
    Serial.print("  "); // Convert the data from the character array (received X value) into integer
    delay(10);
    radio.read(&receivedData, sizeof(receivedData));
    y = atoi(&receivedData[0]);
    Serial.println(y);
    delay(10);
  }
  
  
  

 
  if( y > thresholdy || (-thresholdy) > y ){    
    motorLeft.setSpeed(y);
    motorRight.setSpeed(y);
    Serial.println("C1");
  }
  if( x > thresholdx || (-thresholdx) > x){
    motorLeft.setSpeed((x));
    motorRight.setSpeed(x);
        Serial.println("C2");

  }
    
  if(x <thresholdx && (-thresholdx) < x && y <thresholdx && (-thresholdx) < y){
    motorLeft.setSpeed(0);
    motorRight.setSpeed(0);
    Serial.println("C3");
    }
  
    
  }
