/*
Send ctrl word from ios form and decodes for control*/
//SAMPLE ControlWords 
//"3,2,5,N,2,5,P,2,5,N,2,5,N,*";
//"2,3,10,P,1,2,P,2,3,P,*";
//"1,2,10,P,2,10,P,*"
//"0,2,10,P,*"

//P = PAUSE
//N = NO PAUSE

#include <SimpleTimer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <String.h>
#include <assert.h>

String ref_weight[10];//reference weight
String container[10]; //container 0,1,2,3
String tokens[20];    //buffer 
String ctrlword = "";           // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean recipe_ready = 0;       //set to 1 when ctrlword is decoded
boolean control_ready  = 1;     //set to 1 when dispense is completed
char delimiter = ',';
unsigned long timestart;
unsigned long timeend;
unsigned long time;
int time_flag = 0;

void setup() {
  Serial.begin(57600);    // initialize serial:
  ctrlword.reserve(500);  // reserve 200 bytes for the inputString:
} 

void loop() {
  time = millis();

  if (stringComplete) {
    Serial.println(ctrlword);
    Serial.print("[string printed at time:"); Serial.print(time); Serial.println(" ms] ");

    ctrlword = "";            // RESET, clear string/false
    stringComplete = false;   
   
    /*TO DO Controls*/
    
  }

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read();   // get the new byte:
    ctrlword += inChar;                  // add it to the ctrlword:
    if (inChar == '*') {  
      stringComplete = true;
    }
  }
}
