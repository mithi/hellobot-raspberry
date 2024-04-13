#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BLEEddystone.h"
#include "BluefruitConfig.h"

#define URL "http://mithi.xyz"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
Adafruit_BLEEddystone eddyBeacon(ble);

const int red_led = 13;

void setup(void){
  
  pinMode(red_led, OUTPUT);
  
  while(!ble.begin(!VERBOSE_MODE)); //initialize BLE module
  status_blink(4, 250);
   
  while(!ble.factoryReset()); //reset to factory settings
  ble.echo(false); //disable command echo
  status_blink(8, 100); 
  
  eddyBeacon.begin(true); //enable eddystone beacon service
  while( !eddyBeacon.setURL(URL) ); //set URL  
  status_blink(4, 500);

  digitalWrite(red_led, LOW);
}

void loop(void){
  eddyBeacon.startBroadcast();
}

void status_blink(int n, int d){
  //n - number of times, d - delay in microseconds 

  for(int i = 0; i < n; i++){
    digitalWrite(red_led, HIGH);
    delay(d);
    digitalWrite(red_led, LOW);
    delay(d);
  }
}
