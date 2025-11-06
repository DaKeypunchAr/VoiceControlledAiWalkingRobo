#include "motor.hpp"
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <WebServer.h>
#include <WiFi.h>

WebServer server(80); // 80 is the port.

void setup() {
  Serial.begin(115200);

  WiFi.softAP("DKPBRAIN",
              "firstthingsfirsti'mgoingtosayiswhyareyoureadingthis");
  Serial.print("Wifi IP Address: ");
  Serial.println(WiFi.softAPIP());

  pinMode(2, OUTPUT);
  MotorDriver::setupMotors();

  server.on("/", []() {
    File webpage = LittleFS.open("/index.html", "r");
    server.streamFile(webpage, "text/html");
    webpage.close();
  });

  server.on("/rotateacw", []() {
    Serial.println("Attempted to rotate anti-clockwise/left!");
    MotorDriver::rotateLeft();
  });

  server.on("/rotatecw", []() {
    Serial.println("Attempted to rotate clockwise/right!");
    MotorDriver::rotateRight();
  });
  server.on("/forward", []() {
    Serial.println("Attempted to move forward!");
    MotorDriver::moveForward();
  });
  server.on("/backward", []() {
    Serial.println("Attempted to move backward!");
    MotorDriver::moveBackward();
  });
  server.on("/stop", []() {
    Serial.println("Attempted to stop!");
    MotorDriver::stop();
  });

  server.begin();
}

void loop() { server.handleClient(); }
