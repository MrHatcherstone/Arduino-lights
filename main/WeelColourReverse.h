#ifndef WeelColourReverse_H
#define WeelColourReverse_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel pixels;
extern int diff;
extern int pix_count;
extern int ledPosition;
extern int ledBright;
extern int ledDelay;
extern int int_R;
extern int int_G;
extern int int_B;
extern int colour;
extern unsigned long previousMillis;
extern unsigned long currentMillis;

void WeelColourReverse (){
  currentMillis = millis();
  if (currentMillis - previousMillis >= ledDelay) {
    if (colour <= 255) {
        int_R = 255;
        int_G = 0;
        int_B = 255 - colour;
    } 
    else if (colour <= 510) {
        int_R = colour - 255;
        int_G = 0;
        int_B = 255;
    } 
    else if (colour <= 765) {
        int_R = 0;
        int_G = 765 - colour;
        int_B = 255;
    } 
    else if (colour <= 1020) {
        int_R = 0;
        int_G = 255;
        int_B = colour - 765;
    } 
    else if (colour <= 1275) {
        int_R = 1275 - colour;
        int_G = 255;
        int_B = 0;
    } 
    else {
        int_R = 255;
        int_G = 1530 - colour;
        int_B = 0;
    }
    int_R = int_R * ledBright / 100;
    int_G = int_G * ledBright / 100;
    int_B = int_B * ledBright / 100; 

    pixels.setPixelColor(ledPosition, pixels.Color(int_R, int_G, int_B)); 
    pixels.show();

    if (colour + diff > 1530)
        colour = 0;
    else
      colour += diff;
      
    ledPosition += 1;
    if (ledPosition >= pix_count)
        ledPosition = 0;
    previousMillis = currentMillis;
  }
}

#endif