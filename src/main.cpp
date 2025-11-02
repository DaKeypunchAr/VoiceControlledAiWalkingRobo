#include "esp32-hal-gpio.h"
#include "esp32-hal-ledc.h"
#include <Arduino.h>

unsigned char motor_a1 = 22;
unsigned char motor_a2 = 21;
unsigned char motor_ea = 23;
unsigned char motor_ledc_achannel = 0;

unsigned char motor_b1 = 4;
unsigned char motor_b2 = 18;
unsigned char motor_eb = 19;
unsigned char motor_ledc_bchannel = 1;

void setup() {
  Serial.begin(115200);
  pinMode(motor_a1, OUTPUT);
  pinMode(motor_a2, OUTPUT);
  pinMode(motor_b1, OUTPUT);
  pinMode(motor_b2, OUTPUT);

  pinMode(2, OUTPUT);

  ledcSetup(motor_ledc_achannel, 5000, 8);
  ledcAttachPin(motor_ea, motor_ledc_achannel);
  ledcSetup(motor_ledc_bchannel, 5000, 8);
  ledcAttachPin(motor_eb, motor_ledc_bchannel);

  ledcWrite(motor_ledc_achannel, 255);
  ledcWrite(motor_ledc_bchannel, 255);

  Serial.println("Going to start in 5s!");
  delay(5000);
}

void loop() {
  digitalWrite(motor_a1, LOW);
  digitalWrite(motor_a2, HIGH);
  digitalWrite(motor_b1, LOW);
  digitalWrite(motor_b2, HIGH);

  digitalWrite(2, HIGH);

  delay(1000);

  digitalWrite(motor_a1, HIGH);
  digitalWrite(motor_a2, LOW);
  digitalWrite(motor_b1, HIGH);
  digitalWrite(motor_b2, LOW);

  digitalWrite(2, LOW);

  delay(1000);
}
