#ifndef MOTOR_HPP
#define MOTOR_HPP

// Direction is if you were the car.
enum Wheel { LEFT, RIGHT };

enum Direction { FORWARD, BACKWARD };

namespace MotorDriver {
void setupMotors();
void bindMotor(const Wheel w);
void setMotor(const Direction d, const unsigned char speed);
inline void bindAndSetMotor(const Wheel w, const Direction d,
                            const unsigned char speed) {
  bindMotor(w);
  setMotor(d, speed);
}
void moveForward(const unsigned char speed = 255);
void moveBackward(const unsigned char speed = 255);
void rotateLeft(const unsigned char speed = 255);
void rotateRight(const unsigned char speed = 255);
void stop();
} // namespace MotorDriver

#endif
