#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10); // CE, CSN
const byte address[6] = "12359";
char xyData[32] = "";
String xAxis, yAxis;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  
  xAxis = (analogRead(A7)); // Read Joysticks X-axis
  yAxis = (analogRead(A6)); // Read Joysticks Y-axis
  Serial.print(xAxis);
  Serial.print("  ");
  Serial.println(yAxis);
  // X value
  xAxis.toCharArray(xyData, 5); // Put the String (X Value) into a character array
  radio.write(&xyData, sizeof(xyData)); // Send the array data (X value) to the other NRF24L01 modile
  // Y value
  yAxis.toCharArray(xyData, 5);
  radio.write(&xyData, sizeof(xyData));
  delay(20);
}