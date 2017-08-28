// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time.
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif
 
#define PIN 0
#define LED_NUMBER 32 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_NUMBER, PIN);
 
uint8_t  mode  = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = pixels.Color( 200, 50, 0 ); // Start red
uint32_t prevTime;
 
void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(15); // 1/3 brightness
  prevTime = millis();
}

void turnoff(){
 for(int i=0; i<LED_NUMBER; i++) {
  pixels.setPixelColor(   i, pixels.Color( 0, 0, 0 ));
 }
 pixels.show();
}
void loop() {
  uint8_t  i;
  uint32_t t;
 
  switch(mode) {
 
   case 0: // Random sparks - just one LED on at a time!
   turnoff();
    for(int j=0; j<16; j++) {
       pixels.setPixelColor(   j, color);
       pixels.setPixelColor(31-j, color); // Second eye (flipped)
       pixels.show();
       delay(75);
    }
    for(int j=0; j<16; j++) {
       pixels.setPixelColor(   j, pixels.Color( 0, 0, 0 ));
       pixels.setPixelColor(31-j, pixels.Color( 0, 0, 0 )); // Second eye (flipped)
       pixels.show();
       delay(75);
    }
    break;
 
   case 1: // Spinny wheels (8 LEDs on at a time)
    for(i=0; i<16; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
      pixels.setPixelColor(   i, c); // First eye
      pixels.setPixelColor(31-i, c); // Second eye (flipped)
    }
    pixels.show();
    offset++;
    delay(50);
    break;
    
    case 2: 
      turnoff();
      for(int j=0; j<16; j++) {
         pixels.setPixelColor(   j, color);
         pixels.setPixelColor(31-j, color); // Second eye (flipped)
         pixels.show();
         delay(75);
      }  
      for(int j=0; j < 17; j++) {
         pixels.setPixelColor( 16-j, pixels.Color( 0, 0, 0 ));
         pixels.setPixelColor(15+j, pixels.Color( 0, 0, 0 )); // Second eye (flipped)
         pixels.show();
         delay(75);
      } 
      turnoff();
      break;
    case 3: 
      turnoff();
      for(int j=0; j<16; j++) {
         pixels.setPixelColor(   j, color);
         pixels.setPixelColor(31-j, color); // Second eye (flipped)
         if(j > 0){
            pixels.setPixelColor( j - 1,pixels.Color( 50, 0, 20 ));
            pixels.setPixelColor(31-j +1 ,pixels.Color( 50, 0,20 )); // Second eye (flipped)
            pixels.setPixelColor( 16 - j, color);
            pixels.setPixelColor( 15 + j, color);
         }
         if(j > 1){
          pixels.setPixelColor(  j-2, pixels.Color( 20, 0, 50 ));
          pixels.setPixelColor( 31 - j + 2, pixels.Color( 20, 0, 50 ));
          pixels.setPixelColor( 16 - j + 1,pixels.Color( 20, 0, 50 ) );
          pixels.setPixelColor( 15 + j - 1, pixels.Color( 20, 0, 50 ));
         }     
         if(j > 2){
          pixels.setPixelColor(   j-3, pixels.Color( 0, 0, 50 ));
          pixels.setPixelColor( 31 - j + 3, pixels.Color( 0, 0, 50 ));
          pixels.setPixelColor( 16 - j + 2,pixels.Color( 0, 0, 50) );
          pixels.setPixelColor( 15 + j - 2, pixels.Color( 0, 0, 50 ));
         }        
         pixels.show();
         delay(80);
      }
      break; 
//      for(int j=0; j < 17; j++) {
//         pixels.setPixelColor( 16-j, pixels.Color( 0, 0, 0 ));
//         pixels.setPixelColor(15+j, pixels.Color( 0, 0, 0 )); // Second eye (flipped)
//         pixels.show();
//         delay(75);
//      } 
//      turnoff();
      
  }



  t = millis();
  if((t - prevTime) > 5000) {      // Every 8 seconds...
    mode++;                        // Next mode
    if(mode >= 4) {                 // End of modes?
      mode = 0;                    // Start modes over
      //color >>= 8;                 // Next color R->G->B
      //if(!color) color = 0xFF0000; // Reset to red
    }
    for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}

