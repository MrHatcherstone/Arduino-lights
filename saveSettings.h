#ifndef saveSettings_H
#define saveSettings_H

extern File configFile;
extern int ledBright;
extern int ledDelay;
extern int int_R;
extern int int_G;
extern int int_B;
extern int lightningType;
extern bool workIsFinished;

void saveSettings() {
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to write config file");
    return;
  }
  StaticJsonDocument<256> doc;
  doc["ledDelay"] = ledDelay;
  doc["ledBright"] = ledBright;
  doc["lightningType"] = lightningType;
  doc["r"] = int_R;
  doc["g"] = int_G;
  doc["b"] = int_B;
  char jsonBuffer[256];
  size_t bytesWritten = serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
  configFile.write((const uint8_t *)jsonBuffer, bytesWritten);
  configFile.close();
}

#endif