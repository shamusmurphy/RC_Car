/*
Car class: this class represents an arduino controlled car
Mason Ritchie
*/

#ifndef Car_H
#define Car_H

#include <Arduino.h>
#include <Servo.h>

class Car {
  private:
    // speed
    int speedL;
    int speedR;
    int speed;

    // battery control
    bool engineOn;

    // brake
    bool brake;

    // direction (servo control)
    Servo servo;
    int direction;

    // transmission
    char transmission;

    // pins
    int ep; // engine pin
    int dp; // direction pin

    // constants
    const int lsp = 3; // left speed pin
    const int rsp = 11; // right speed pin
    const int lbp = 9; // left break pin
    const int rbp = 8; // right break pin
    const int ldp = 12; // left direction pin
    const int rdp = 13; // right direction pin
    

  public:
    // constructor (engine pin, direction pin)
    Car(int enginePin, int directionPin) {
      // set vars
      this->speedL = 0;
      this->speedR = 0;
      this->speed = 0;
      this->engineOn = false;
      this->brake = true;
      this->direction = 90;
      this->transmission = 'p';
      this->ep = enginePin;
      this->dp = directionPin;

      // set pin modes
      pinMode(lsp, OUTPUT);
      pinMode(rsp, OUTPUT);
      pinMode(lbp, OUTPUT);
      pinMode(rbp, OUTPUT);
      pinMode(ldp, OUTPUT);
      pinMode(rdp, OUTPUT);
      pinMode(ep, OUTPUT);

      // set servo pin
      servo.attach(dp);
    }

    // updates Car to right status
    void update() {
      // checks and sets brakes
      if (brake == true) { // brake on
        digitalWrite(lbp, HIGH);
        digitalWrite(rbp, HIGH);
      }
      else if (brake == false) { // brake off
        digitalWrite(lbp, LOW);
        digitalWrite(rbp, LOW);
      }

      // checks transmission and updates speed
      if (transmission == 'f') { // drive
        digitalWrite(ldp, HIGH);
        digitalWrite(rdp, HIGH);
      }
      else if (transmission == 'r') { // reverse
        digitalWrite(ldp, LOW);
        digitalWrite(rdp, LOW);
      }

      // sets direction angle
      servo.write(direction);

      // updates speed
      analogWrite(lsp, speedL);
      analogWrite(ldp, speedR);
    }

    // turns engine on or off
    void engineTurn(bool turn) {
      if (turn == true) { // on
        engineOn = true;
        digitalWrite(ep, HIGH);
      }
      else if(turn == false) { // off
        engineOn = false;
        digitalWrite(ep, LOW);
      }
    }

    // shift car between parked('p'), drive('f'), and reverse('r')
    void shiftTrans(char pos) {
      if (pos == 'p') { // parked
        transmission = 'p';
        brake = true;
      }
      else if (pos == 'f') { // drive
        transmission == 'f';
        brake = false;
      }
      else if (pos == 'r') { // reverse
        transmission == 'r';
        brake = false;
      }

      // zeros speed
      speedL = 0;
      speedR = 0;
    }

    // sets cars axel 5 degrees to the left
    void turnLeft() {
      if (direction < 180) {
        direction = direction + 5;
      }
    }

    // sets the cars axel 5 degrees to the right
    void turnRight() {
      if (direction < 0) {
        direction = direction - 5;
      }
    }

    // set speed
    // either increments speed up and down (gas pedal) or set an exact speed (throttle)
    void increaseSpeed() {
      speed = speed + 5;
      setSpeed();
    }
    void decreaseSpeed() {
      speed = speed - 5;
      setSpeed();
    }
    void setSpeed() {
      speedL = speed;
      speedR = speed;
    }
    int getSpeed() {
      return speed;
    }

};

#endif