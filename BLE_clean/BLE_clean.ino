/*
Send ctrl word from ios form and decodes for control*/
//SAMPLE ControlWords 
//"3,2,5,N,2,5,P,2,5,N,2,5,N,*";
//"2,3,10,P,1,2,P,2,3,P,*";
//"1,2,10,P,2,10,P,*"
//"0,2,10,P,*"

//P = PAUSE
//N = NO PAUSE
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
void controlfxn(){
  if(recipe_ready == 1){
    Serial.print("..printing...\n");
    delay(10000);
    control_ready = 1;
    Serial.print("control_ready = 1\n");
  }
}
void ParseCtrlWord(String ctrl){
  int commaIndex = ctrl.indexOf(delimiter);
  int secondCommaIndex = 1; 

  //extract array size
  String value = ctrl.substring(0, commaIndex);
  int arr_size = value.toInt() + 1;
      for(int i = 0; i < arr_size*3 ; i ++){
        commaIndex = secondCommaIndex + 1;
        secondCommaIndex = ctrl.indexOf(delimiter,commaIndex);
        value = ctrl.substring(commaIndex, secondCommaIndex);
        tokens[i] = value;
        if(value == "*") break;
      }

  //validate tokens 
  //load alternate values into the arrays
     Serial.print("tokens array = ");
  for(int j = 0; j < 20; j++){
      Serial.print(tokens[j]);
  }    
      Serial.print(" \n");

  //tokens= "2,5,N,2,5,N,2,5,N,2,5,N,*";
  for(int j = 0; j < 4; j++){
    container[j*2] = tokens[j*3];
    ref_weight[j*2] = tokens[j*3+1];
    container[j*2+1] = tokens[j*3+2];
    ref_weight[j*2+1] = tokens[j*3+2];
  }    
  container[arr_size*2] = "*";
  ref_weight[arr_size*2] = "*";

//print out ref_weight
//3,P,1,P,2,P
Serial.print("reference weight = ");
  for(int l = 0; l < (arr_size*2)+1; l++){
    Serial.print(container[l]);
    Serial.print(" ");
  }    
  Serial.print(" \n");

  
//print out container
//10,P,2,P,3,P
Serial.print("container = ");
  for(int k = 0; k < (arr_size*2)+1; k++){
    Serial.print(ref_weight[k]);
    Serial.print(" ");
  }    
  Serial.print("\n\n");
  recipe_ready = 1;
  Serial.print("recipe_ready = 1\n");
  }

