#ifndef Randomizer_H
#define Randomizer_H

#include <Adafruit_NeoPixel.h>
extern Adafruit_NeoPixel pixels;
extern int pix_count;
extern int ledPosition;
extern int ledBright;
extern int ledDelay;
extern unsigned long previousMillis;
extern unsigned long currentMillis;

void Randomizer (){
  currentMillis = millis();;
  if (currentMillis - previousMillis >= ledDelay) {
    pixels.setPixelColor(ledPosition, pixels.Color((random (0,255) * ledBright / 100), (random (0,255) * ledBright / 100), (random (0,255) * ledBright / 100))); 
    pixels.show();    

    ledPosition += 1;
    if (ledPosition >= pix_count)
      ledPosition = 0;
    previousMillis = currentMillis;
  }
}

#endif