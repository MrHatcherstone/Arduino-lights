#ifndef WeelColourPinkBlue_H
#define WeelColourPinkBlue_H

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

void WeelColourPinkBlue (){
  
  currentMillis = millis();
  if (currentMillis - previousMillis >= ledDelay) {
    if (colour <= 255) { // фиолетовый - синий
        int_R = 255 - colour;
        int_B = colour;
    }
    else { // синий - фиолетовый 
        int_R = colour - 255;
        int_B = 510 - colour;
    } 

    int_R = int_R * ledBright / 100;
    int_B = int_B * ledBright / 100; 

    pixels.setPixelColor(ledPosition, pixels.Color(int_R, 0, int_B)); 
    pixels.show();
    
    if (colour + diff > 510 )
        colour = diff;
    else
      colour += diff;
      
    ledPosition += 1;
    if (ledPosition >= pix_count)
        ledPosition = 0;
    previousMillis = currentMillis;
  }
}

#endif
