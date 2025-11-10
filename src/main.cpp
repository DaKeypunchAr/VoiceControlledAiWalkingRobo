#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <WebServer.h>
#include <WiFi.h>
#include "motor.hpp"
#include "HTTPClient.h"
#include "ArduinoJson.h"
#include "Audio.h"

#define WIFI_SSID "WIFI_NAME"
#define WIFI_PASSWORD "0123456789"

#define API_KEY "AIzaSyCOnbhdDm-EBXiTuVaBw5pf7dnfmnAY44E"
#define API_URL "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent?key=" API_KEY

Audio audio;

#define AUDIO_BIT_CLOCK_PIN 0
#define AUDIO_LEFT_RIGHT_SWITCH_PIN 0
#define AUDIO_DATA_PIN 0
#define AUDIO_VOLUME 15
  
void setup() {
  Serial.begin(115200);

  if (!AUDIO_BIT_CLOCK_PIN || !AUDIO_LEFT_RIGHT_SWITCH_PIN || !AUDIO_DATA_PIN) {
    Serial.println("Audio connection pins are not labelled");
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  connectToWifi();

  audio.setPinout(AUDIO_BIT_CLOCK_PIN, AUDIO_LEFT_RIGHT_SWITCH_PIN, AUDIO_DATA_PIN);
  audio.setVolume(AUDIO_VOLUME);
}

void connectToWifi() {
  Serial.println("Attempting to connect to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    if (++attempts % 10 == 0) {
      Serial.print("Check for the WiFi connection! ");
      Serial.print(attempts);
      Serial.println(" attempts reached!");
    }
  }
}

String promptAi(const String prompt) {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWifi();
  }

  HTTPClient http;
  String payload = "{"
                   "\"contents\": [{"
                   "  \"parts\": [{"
                   "    \"text\": \"" + prompt + "\""
                   "  }]"
                   "}],"
                   "\"generationConfig\": {"
                   "  \"temperature\": 0.9,"
                   "  \"maxOutputTokens\": 150"
                   "}"
                   "}"; 
  
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(payload);
  if (httpCode <= 0) {
    Serial.println("Request failed. Check internet or API key.");
    http.end();
    return "Connection didn't take place due to some thing for which you need to check the real values and i'm lazy to do them";
  }
  
  String response = http.getString();
  http.end();

  if (httpCode != 200) {
    Serial.println("HTTP Error: " + String(httpCode));
    return "Unsucessful Connection";
  }
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.println("JSON parse error: " + String(error.c_str()));
    return "Some JSON parse error!";
  }

  if (doc.containsKey("candidates") && doc["candidates"].size() > 0) {
    return doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();
  } 
  Serial.println("No reply from Gemini. Check API key or quota.");
  return "No reply....";
}

void speak(const String joke) {
  Serial.print("Gemini said: ");
  Serial.println(joke);
  delay(1000);
}

void loop() {
  String joke = promptAi("Get me a random joke that is funny infact!");
  speak(joke);
}

