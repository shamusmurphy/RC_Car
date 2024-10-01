// Car class: this class represents an arduino controlled car
// Mason Ritchie

#ifndef Car_H
#define Car_H

#include <Arduino.h>

class Car {
  public:
    // speed
    int speedL;
    int speedR;

    // battery control
    bool engineOn;

    // brake
    bool brake;

    // direction (servo control)
    int direction;

    // transmission
    char transmission;
    

  private:
    // constructor
    car() {
      this->speedL = 0;
      this->speedR = 0;
      this->engineOn = false;
      this->brake = true;
      this->direction = 90;
      this->transmission = 'p';
    }

    // updates Car to right status
    void update() {
      if (transmission == 'p') {

      }
      else if (transmission == 'f') {

      }
      else if (transmission == 'r') {

      }
      else {
        Serial.println("out of gear");
        transmission = 'p';

      }
    }

    // turns engine on or off
    void engineTurn(bool turn) {
      if (turn == true) { // on
        engineOn = true;
        digitalWrite(3, HIGH);
      }
      else (turn == false) { // off
        engineOn = false;
        digitalWrite(3, LOW);
      }
    }

    // shift car
    void shiftTrans(char pos) {
      if (pos == 'p') {
        transmission = 'p';
      }
      else if (pos == 'f') {
        transmission == 'f';
      }
      else if (pos == 'r') {
        transmission == 'r';
      }
      else {
        Serial.println("invalid shift")
      }
    }
};

#endif