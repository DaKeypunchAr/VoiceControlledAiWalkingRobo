#include "motor.hpp"
#include "Arduino.h"

constexpr unsigned char motor_a1 = 22;
constexpr unsigned char motor_a2 = 21;
constexpr unsigned char motor_ea = 23;
constexpr unsigned char motor_ledc_achannel = 0;

constexpr unsigned char motor_b1 = 4;
constexpr unsigned char motor_b2 = 18;
constexpr unsigned char motor_eb = 19;
constexpr unsigned char motor_ledc_bchannel = 1;

unsigned char motor_1 = 0;
unsigned char motor_2 = 0;
unsigned char motor_e = 0;

namespace MotorDriver {
void setupMotors() {
  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);

  ledcSetup(motor_ledc_achannel, 5000, 8);
  ledcAttachPin(motor_ea, motor_ledc_achannel);
  ledcSetup(motor_ledc_bchannel, 5000, 8);
  ledcAttachPin(motor_eb, motor_ledc_bchannel);

  ledcWrite(motor_ledc_achannel, 255);
  ledcWrite(motor_ledc_bchannel, 255);
}

void bindMotor(const Wheel w) {
  if (w == Wheel::RIGHT) {
    motor_1 = motor_a1;
    motor_2 = motor_a2;
    motor_e = motor_ea;
    return;
  }
  motor_1 = motor_b1;
  motor_2 = motor_b2;
  motor_e = motor_eb;
}

void setMotor(const Direction d, const unsigned char speed) {
  digitalWrite(motor_1, d == Direction::BACKWARD);
  digitalWrite(motor_2, d == Direction::FORWARD);
}
void moveForward(const unsigned char speed) {
  MotorDriver::bindAndSetMotor(Wheel::LEFT, Direction::FORWARD, speed);
  MotorDriver::bindAndSetMotor(Wheel::RIGHT, Direction::FORWARD, speed);
}

void moveBackward(const unsigned char speed) {
  MotorDriver::bindAndSetMotor(Wheel::LEFT, Direction::BACKWARD, speed);
  MotorDriver::bindAndSetMotor(Wheel::RIGHT, Direction::BACKWARD, speed);
}

void rotateLeft(const unsigned char speed) {
  MotorDriver::bindAndSetMotor(Wheel::LEFT, Direction::BACKWARD, speed);
  MotorDriver::bindAndSetMotor(Wheel::RIGHT, Direction::FORWARD, speed);
}

void rotateRight(const unsigned char speed) {
  MotorDriver::bindAndSetMotor(Wheel::LEFT, Direction::FORWARD, speed);
  MotorDriver::bindAndSetMotor(Wheel::RIGHT, Direction::BACKWARD, speed);
}

void stop() {
  MotorDriver::bindAndSetMotor(Wheel::LEFT, Direction::FORWARD, 0);
  MotorDriver::bindAndSetMotor(Wheel::RIGHT, Direction::BACKWARD, 0);
}
} // namespace MotorDriver
