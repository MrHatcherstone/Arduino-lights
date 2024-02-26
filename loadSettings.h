#ifndef loadSettings_H
#define loadSettings_H

extern File configFile;
extern int ledBright;
extern int ledDelay;
extern int int_R;
extern int int_G;
extern int int_B;
extern int lightningType;
extern bool workIsFinished;

void loadSettings() {
  
  if (SPIFFS.exists("/config.json")) {
    configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
      Serial.println("Failed to open config file");
      return;
    }
  } else {
    configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("Failed to write config file");
    } else {
      StaticJsonDocument<256> doc;
      doc["ledDelay"] = 0;
      doc["ledBright"] = 0;
      doc["lightningType"] = 0;
      doc["r"] = 0;
      doc["g"] = 0;
      doc["b"] = 0;
      char jsonBuffer[256];
      size_t bytesWritten = serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));
      configFile.write((const uint8_t *)jsonBuffer, bytesWritten);
      configFile.close();
    }
    return;
  }
  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return;
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  configFile.close();
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());
  char jsonBuffer[1024];
  serializeJsonPretty(doc, jsonBuffer);

  if (error) {
    Serial.println("Failed to parse config file");
    return;
  }
  ledDelay = doc["ledDelay"];
  ledBright = doc["ledBright"];
  lightningType = doc["lightningType"];
  int_R = doc["r"];
  int_G = doc["g"];
  int_B = doc["b"];
  if (lightningType != 0) {
    workIsFinished = false;
  }
}

#endif