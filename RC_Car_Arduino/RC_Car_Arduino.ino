/*
Mason Ritchie
This code receives serial input from the raspberry pi and interprets it
to commands to be carried out by the Arduino Uno and motor sheild.
*/

#include "Car.h"

int input;

void setup() {
  // left wheel
  pinMode(12, OUTPUT); // direction
  pinMode(9, OUTPUT); // break
  // digital pin: 3 - speed

  // right wheel
  pinMode(13, OUTPUT); // direction
  pinMode(8, OUTPUT); // break
  // digital pin: 11 - speed

  // axel servo
  pinMode(2, OUTPUT);

  // setup serial communication
  Serial.begin(9600);

}

void loop() {
  input = NULL;
  if (Serial.available() > 0) { // checks for serial message
    input = Serial.read();
    delay(10);

  }

  if (input != NULL) { // checks if input was recived
    Serial.print("code: ");
    Serial.print(input);
    Serial.println(" received");
  }

  switch (input) {
    case 'b':
      Serial.println("is b");
      Serial.end();
      break;

    default:
      Serial.println("unrecognized code");
      break;
  }
}
