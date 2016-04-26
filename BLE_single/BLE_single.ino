/*
Send ctrl word from ios form and decodes for control*/
//SAMPLE ControlWords 
//"3, 2,5,N,2,5,P,2,5,N,2,5,N,*";
//"2, 3,10,P,1,2,P,2,3,P,*";
//"1, 2,10,P,2,10,P,*"
//"0, 2,10,P,*"

//P = PAUSE
//N = NO PAUSE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <String.h>
#include <assert.h>

//variables
String main_arr2[20];
String main_arr1[20];    //buffer 
String ctrlword = "";           // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean recipe_ready = 0;       //set to 1 when ctrlword is decoded
boolean control_ready  = 1;     //set to 1 when dispense is completed
char delimiter = ',';

void setup() {
  Serial.begin(57600);    // initialize serial:
  ctrlword.reserve(500);  // reserve 200 bytes for the inputString:
} 

void loop() {
  if (stringComplete) {
    Serial.print("Control word: ");
    Serial.println(ctrlword);

    if(control_ready == 1){
      ParseCtrlWord(ctrlword);
    }
    controlfxn();
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

/* controlfxn -- mock control, time delay which sets 
 *               the control_ready signal 
 */
void controlfxn(){
  if(recipe_ready == 1){
    Serial.print("..printing...\n");
    delay(10000);
    control_ready = 1;
    Serial.print("control_ready = 1\n\n");
  }
}

/* ParseCtrlWord
 * converts control word into 3 arrays
 * reference weight & container & pauses
 */
void ParseCtrlWord(String ctrl){
  int commaIndex = ctrl.indexOf(delimiter);
  int secondCommaIndex = 1; 

  //extract array size
  String value = ctrl.substring(0, commaIndex);
  int arr_size = value.toInt() + 1;
  
  Serial.print("each array size will should be = "); Serial.print(arr_size*2+1); Serial.print(" \n");
    int i;
      for(i = 0; i < arr_size*3 ; i ++){
        commaIndex = secondCommaIndex + 1;
        secondCommaIndex = ctrl.indexOf(delimiter,commaIndex);
        value = ctrl.substring(commaIndex, secondCommaIndex);
        main_arr1[i] = value;
        if(value == "*") break;
      }
    main_arr1[i-1] = "-1";

  //print out main_arr1
  //3,P,1,P,2,P
  Serial.print("main_arr1 = ");
    for(int l = 0; l < ((arr_size*2)*3)+1 ; l++){
      Serial.print(main_arr1[l]);
      Serial.print(" ");
    }    
    Serial.print(" \n");
    Serial.print(" \n");
    recipe_ready = 1;
    Serial.print("recipe_ready = 1\n");
   }

