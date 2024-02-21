#include <CytronMotorDriver.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define LEFT_MOTOR_PWM 3
#define LEFT_MOTOR_DIR 4
#define RIGHT_MOTOR_PWM 5
#define RIGHT_MOTOR_DIR 6

#define thresholdx 10
#define thresholdy 10

CytronMD motorLeft(PWM_DIR, LEFT_MOTOR_PWM, LEFT_MOTOR_DIR);
CytronMD motorRight(PWM_DIR, RIGHT_MOTOR_PWM, RIGHT_MOTOR_DIR);

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "12359";

struct JoystickData {
  int xAxis;
  int yAxis;
};

JoystickData joystickData;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&joystickData, sizeof(joystickData)); // Read entire struct

    int x = joystickData.xAxis;
    int y = joystickData.yAxis;

    Serial.print(x);
    Serial.print("  ");
    Serial.println(y);

    if (abs(y) > thresholdy || abs(x) > thresholdx) {
      int speed = (y + x) / 2; // Adjust the calculation based on your joystick mapping
      motorLeft.setSpeed(speed);
      motorRight.setSpeed(speed);
    } else {
      motorLeft.setSpeed(0);
      motorRight.setSpeed(0);
    }
  }
}