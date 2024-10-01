/*
Mason Ritchie
This code receives serial input from the raspberry pi and interprets it
to commands to be carried out by the Arduino Uno and motor sheild.
*/

#include "Car.h"

int input;
Car car(4, 2); // Car object

void setup() {
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

  // executes command based on input
  switch (input) {
    case 'o': // turn engine on
      car.engineTurn(true);
      Serial.println("engine is on");
      break;
    case 'i': // turn engine off
      car.engineTurn(false);
      Serial.println("engine is off");
      break;
    case 'l': // turn left
      car.turnLeft();
      Serial.println("turning left");
      break;
    case 'r': // turn right
      car.turnRight();
      Serial.println("turning right");
      break;
    case 'f': // transmission: forward
      car.shiftTrans('f');
      Serial.println("car in drive");
      break;
    case 'b': // transmission: reverse
      car.shiftTrans('r');
      Serial.println("car in reverse");
      break;
    case 'p': // transmission: parked
      car.shiftTrans('p');
      Serial.println("car in park");
      break;
    case 's': // sets speed
      input = Serial.read();
      car.setSpeed(input);
      Serial.print("speed set to: ");
      Serial.println(input);
      break;
    default: // unrecognized code
      Serial.println("unrecognized code");
      break;
  }

  // update cars status
  car.update();
}
