#ifndef TANK_CONTROL_H
#define TANK_CONTROL_H

#include <string>
#include <arduino.h>

/* ESP pins in order as they appear on the board */
#define L_MOTOR_FWD 14
#define L_MOTOR_REV 12
#define R_MOTOR_FWD 13
#define R_MOTOR_REV 15

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

class Tank_DCMotor {
private:
public:
  Tank_DCMotor(void);
  void run(uint8_t); // byte and uint8_t are the same thing
};

#endif
