#ifndef TANK_CONTROL_CPP
#define TANK_CONTROL_CPP
#include "tank_control.h"

Tank_DCMotor::Tank_DCMotor(void) {

}

void run(byte cmd) {
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);
  // switch(cmd) {
  //   case FORWARD:
  //     break;
  //   case BACKWARD:
  //     break;
  // }
}

#endif
