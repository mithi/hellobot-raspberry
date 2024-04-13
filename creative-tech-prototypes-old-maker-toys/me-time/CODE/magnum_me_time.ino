#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "space_invaders.h"
#include "songs.h"
#include <RTCZero.h>

#define NUMBER_OF_SONGS 33
#define NOISE 40
#define MIC_PIN A0
#define MIC_THRESHOLD 200
#define PIEZO_PIN 13 
#define NEOPIXEL_PIN 12
#define NUMBER_OF_NEOPIXELS 12
#define BATTERY_CHECK_PIN A7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_NEOPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
RTCZero rtc;
boolean alarm_state = false;

/* Change these values to set the current initial time and date*/
const byte seconds = 0;
const byte minutes = 41;
const byte hours = 19;
const byte day = 19;
const byte month = 9;
const byte year = 16;
const byte alarm_hours =  hours;
const byte alarm_minutes = 45;
const byte alarm_seconds = 0;

void setup() {
  
  matrix.begin(0x70);
  initialize_neopixel();  
  initialize_clock();
  
  twelve_seconds();
  twelve_seconds();
  tests();
}



void loop() { 
  
  if(alarm_state){
    
    alarm_state = false;
    magnum_its_your_time();    
  
  }else{
    
    int x = microphone_reading();
    display_loudness_level(x);
    
    if (x > MIC_THRESHOLD){
      if(battery_low) beep3x();
      clock_routine();
    }
  }
}

void alarm_match(){
  alarm_state = true; 
}

void magnum_its_your_time(){
  
  rainbowCycle(5);
  play_rtttl(songs[int(random(0, 100)) % NUMBER_OF_SONGS]); //0 to 33
  
  scroll_text("It's your time! - Magnum!", 0);
  scroll_text(" ", 0);

  neopixel_animation2();
}

void clock_routine(){
  
  String am_or_pm = String("am");
  int x = int(rtc.getHours());
  
  if (x > 12) {
    x-=12;
    am_or_pm = String("pm");
  }

  String date_time = String( String(x) + ":" + String(int(rtc.getMinutes())) +  am_or_pm + " " +
                             get_month_name(rtc.getMonth())  + String(rtc.getDay()));
  
  scroll_text(date_time, 0);
}

void display_loudness_level(int microphone_reading){
 
 int x = map(microphone_reading, 0, 600, 0, NUMBER_OF_NEOPIXELS); 
 x--;
 
 for(int i=0; i<= x;i++){
    
    if(i == -1) break;
    
    strip.setPixelColor(i, strip.Color(random(0, 200), random(0, 200), random(0, 200))); 
    strip.show();
    delay(10);
  } 
  
 for(int i= 0; i<= NUMBER_OF_NEOPIXELS;i++)   
    strip.setPixelColor(i, strip.Color(0, 0,0)); 
  
  strip.show();
}

boolean battery_low(){
  float measuredvbat = analogRead(BATTERY_CHECK_PIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  return measuredvbat < 3.3 ? true : false; 
}
void tests(){

  theaterChaseRainbow(50);  
  theaterChase(strip.Color(127, 127, 127), 20); // White
  theaterChase(strip.Color(127, 0, 0), 20); // Red
  theaterChase(strip.Color(0, 0, 127), 20); // Blue
  rainbow(30);
  display_bitmap(square_x);
  matrix.clear();
  String test = "hello world";
  int x = 352;
  scroll_text(test, 0);
  test = String("mutated" + String(x));
  scroll_text(test, 1);
  delay(500);
  rainbowCycle(10);
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  //colorWipe(strip.Color(0, 0, 0), 10);
  
  play_rtttl(songs[26]);
  play_rtttl(songs[27]);
  play_rtttl(songs[28]);
  play_rtttl(songs[29]);

  display_animation(alien_1A, alien_1B, alien_1A, alien_1B, 2);
  display_animation(alien_2A, alien_2B, alien_1A, alien_2B, 2);
  display_animation(alien_3A, alien_3B, alien_3A, alien_3B, 2);  
  display_animation(alien_4A, alien_4B, alien_4C, alien_4D, 4);
  
  scroll_text(String(" "), 0);
}


