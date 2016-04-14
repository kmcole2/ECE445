//"3,2,5,N,2,5,N,2,5,N,2,5,N,*";
//"2,3,10,P,1,2,P,2,3,P,*";
//"1,2,10,P,2,10,P,*"
//"0,2,10,P,*"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//char** str_split(char* a_str, const char a_delim);
int arr_size;
int flag = 1;
String ref_weight[10];
String container[10];
String sampl = "2,3,10,P,1,2,P,2,3,P,*";
String tokens[20];

char * endchar = "*";
String Strings;
boolean recipe_ready = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
}


void loop() {
  // put your main code here, to run repeatedly:


      int commaIndex = sampl.indexOf(',');
      int secondCommaIndex = 1; 

      //extract array size
      String value = sampl.substring(0, commaIndex);
      Strings = value; 
      arr_size = Strings.toInt() + 1;

      Serial.print("arr size = ");
      Serial.print(arr_size);
      Serial.print("\n");

        Serial.print(" firstComma = ");
        Serial.print(commaIndex); 
        Serial.print("\n");     
                Serial.print("\n");       
        
      for(int i = 0; i < 10; i ++){
        commaIndex = secondCommaIndex + 1;
        secondCommaIndex = sampl.indexOf(',',commaIndex);
        Serial.print(" firstIdx = ");
        Serial.print(commaIndex); 
        Serial.print("\n");       
        Serial.print(" secondIdx = ");
        Serial.print(secondCommaIndex);
        Serial.print("\n");
        value = sampl.substring(commaIndex, secondCommaIndex);
        Serial.print(value);
        tokens[i] = value;
        if(value == "*"){
          break;
         }

//        Serial.print(tokens[i]);
        Serial.print(" \n");
      }
      Serial.print("breaks ");        Serial.print(" \n");



  //validate tokens 
  //load alternate values into the arrays
  for(int j = 0; j < 20; j++){
      Serial.print(tokens[j]);
      Serial.print(" ");
  }    
  Serial.print("individ arr size = ");
  Serial.print((arr_size*3 + 2)/3);
    Serial.print("\n");  
    
  for(int j = 0; j < (arr_size*3 + 2)/3 ; j++){
    Serial.print(j);
    Serial.print("idx1 = ");
    Serial.print(j*2);
    Serial.print("\n");
    Serial.print("idx2 = ");
    Serial.print(j*2 + 1);   
        Serial.print("\n"); 
    container[j*2] = tokens[j*3];
    ref_weight[j*2] = tokens[j*3+1];
    container[j*2+1] = tokens[j*3+2];
    ref_weight[j*2+1] = tokens[j*3+2];
  }    
    Serial.print("\n");

//print out container
//10,P,2,P,3,P
  for(int k = 0; k < (arr_size*2); k++){
    Serial.print(ref_weight[k]);
    Serial.print(" ");
  }    
     Serial.print("\n");

//print out ref_weight
//3,P,1,P,2,P
  for(int l = 0; l < (arr_size*2); l++){
    Serial.print(container[l]);
    Serial.print(" ");
  }    
  
  delay(10000);  //10 seconds ?
}

