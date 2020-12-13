#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN     2
#define NUM_LEDS    10

int brightness = 75;

// Declare our NeoPixel objects:
Adafruit_NeoPixel lightStrip(NUM_LEDS, LED_PIN, NEO_RGB + NEO_KHZ800);
// Adafruit_NeoPixel lightStripDownlighter(LEDDOWNLIGHT_COUNT, LEDDOWNLIGHT_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel lightStrip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

boolean gettingBrighter=true;
void setup() {

  Serial.begin(9600);
  lightStrip.begin();           // INITIALIZE NeoPixel lightStrip object (REQUIRED)
  lightStrip.show();            // Turn OFF all pixels ASAP
  lightStrip.setBrightness(75); // Set inital BRIGHTNESS (max = 255)

  
}

void loop() {
  //lightStrip.clear();
  
    colorWipe(lightStrip.Color(0,150,0), 4);

    //lightStrip.setPixelColor(i, lightStrip.Color(0, 150, 0));
    if(gettingBrighter){
      if(brightness < 255){
        brightness+=5;
      }else{
        gettingBrighter=false;
      }
    }
    if(!gettingBrighter){
      if(brightness > 10){
      brightness-=5;
      }else{
       gettingBrighter=true;
      }
    }
    
    

 

  // rainbowCycle(20);
 //theaterChaseRainbow(50);

  //phaseInAndOut(100);
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// lightStrip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  //Serial.println("In Color wipe");
  for(int i=0; i<lightStrip.numPixels(); i++) { // For each pixel in strip...
    lightStrip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    //Serial.println("brightness");
    //Serial.println(brightness);
    lightStrip.setBrightness(brightness);
    lightStrip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void phaseInAndOut(uint8_t speed){

  for(uint16_t i=0; i<256; i++){
    lightStrip.setBrightness(i);
     lightStrip.setPixelColor(i, lightStrip.Color(0, 150, 0));
    lightStrip.show();
    delay(speed);
  }
}
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< lightStrip.numPixels(); i++) {
      lightStrip.setPixelColor(i, Wheel(((i * 256 / lightStrip.numPixels()) + j) & 255));
    }
    lightStrip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return lightStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return lightStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return lightStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < lightStrip.numPixels(); i=i+3) {
        lightStrip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      lightStrip.show();

      delay(wait);

      for (uint16_t i=0; i < lightStrip.numPixels(); i=i+3) {
        lightStrip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < lightStrip.numPixels(); i=i+3) {
        lightStrip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      lightStrip.show();

      delay(wait);

      for (uint16_t i=0; i < lightStrip.numPixels(); i=i+3) {
        lightStrip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
