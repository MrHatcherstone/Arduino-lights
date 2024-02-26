#ifndef staticColour_H
#define staticColour_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel pixels;
extern int pix_count;
extern int ledPosition;
extern int ledBright;
extern int ledDelay;
extern int int_R;
extern int int_G;
extern int int_B;
extern int tempLedPosition;
extern bool workIsFinished;
extern unsigned long previousMillis;
extern unsigned long currentMillis;

void staticColour(){
  currentMillis = millis();
  if (currentMillis - previousMillis >= ledDelay) {
    pixels.setPixelColor(ledPosition, pixels.Color(int_R * ledBright / 100, int_G * ledBright / 100, int_B * ledBright / 100)); 
    pixels.show();;
    ledPosition += 1;
    if (ledPosition >= pix_count)
      ledPosition = 0;
    if (ledPosition == tempLedPosition)
        workIsFinished = true;
    previousMillis = currentMillis;
  }
}

#endif
