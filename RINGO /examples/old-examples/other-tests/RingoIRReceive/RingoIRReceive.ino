#include "IRremote.h"

#define IR_Enable_Front 13
#define IR_Enable_RearLeft 12
#define IR_Enable_RearRight 11
#define IR_Send 10

const int recvPin = 3;
IRrecv irrecv(recvPin);

void  setup ( ){
  Serial.begin(57600);   
  irrecv.enableIRIn();  

  transmitInit();
}

void  loop ( ){
  decode_results  results;        // Somewhere to store the results

  if (irrecv.decode(&results)) {  // Grab an IR code
    dumpInfo(&results);           // Output the results
    Serial.println("");           // Blank line between entries
    irrecv.resume();              // Prepare for the next value
  }
}

void  dumpInfo (decode_results *results){

  // Check if the buffer overflowed
  if (results->overflow) {
    Serial.println("IR code too long. Edit IRremoteInt.h and increase RAWLEN");
    return;
  }

  // Show Code & length
  Serial.print("Code      : ");
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
}


void transmitInit(){
  digitalWrite(IR_Enable_Front, HIGH); //Enable Front IR source 
  digitalWrite(IR_Enable_RearLeft, HIGH); //Enable RearLeft IR source 
  digitalWrite(IR_Enable_RearRight, HIGH); //Enable RearRight IR source
  //Set any of these to LOW to disable the given source

  digitalWrite(IR_Send, HIGH); //Turns ON all enabled IR Light Sources 
  digitalWrite(IR_Send, LOW);  //Turns OFF all enabled IR Light Sources
}

