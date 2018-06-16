int wait = 10;

void twelve_seconds(){

  int reds[] =  {1,0,0,1,1,0,2,0,1,1,0,2};
  int blues[] =  {0,1,0,1,0,1,1,2,0,2,1,0};
  int greens[] = {0,0,1,0,1,1,0,1,2,0,2,1};
  
  for(int i = 0; i < 12; i++){
    pixels.setPixelColor(i, pixels.Color(reds[i]*75, greens[i]*75, blues[i]*75)); 
    pixels.show();
    delay(250);
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}

void neopixel_animation2(){
  colorWipe(pixels.Color(255, 0, 255), 20); 
  colorWipe(pixels.Color(0, 255, 255), 20); 
  colorWipe(pixels.Color(255, 255, 0), 20); 
  colorWipe(pixels.Color(0, 0, 0), 10);  
}

void neopixel_animation1(){
  theaterChase(pixels.Color(127, 0, 127), 20); 
  theaterChase(pixels.Color(127, 127, 0), 20); 
  theaterChase(pixels.Color(0, 127, 127), 20); 
  theaterChase(pixels.Color(0, 0, 0), 20);  
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<NUMBER_OF_PIXELS; i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<NUMBER_OF_PIXELS; i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMBER_OF_PIXELS; i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / NUMBER_OF_PIXELS) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUMBER_OF_PIXELS; i=i+3) {
        pixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < NUMBER_OF_PIXELS; i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUMBER_OF_PIXELS; i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < NUMBER_OF_PIXELS; i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
