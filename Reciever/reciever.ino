#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10); // CE, CSN
const byte address[6] = "12359";

struct JoystickData {
  int xAxis;
  int yAxis;
};

JoystickData joystickData;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  joystickData.xAxis = analogRead(A7);
  joystickData.yAxis = analogRead(A6);

  Serial.print(joystickData.xAxis);
  Serial.print("  ");
  Serial.println(joystickData.yAxis);

  radio.write(&joystickData, sizeof(joystickData)); // Sending entire struct

  delay(20);
}