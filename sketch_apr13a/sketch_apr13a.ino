//"3,2,5,N,2,5,N,2,5,N,2,5,N,**";
//"2,3,10,P,1,2,P,2,3,P,**";
//"1,2,10,P,2,10,P,**"
//"0,2,10,P,**"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//char** str_split(char* a_str, const char a_delim);
int arr_size;
int flag = 1;
char ref_weight[10];
char canister[10];
char * endchar = "*";
String Strings;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
      String sampl = "0,2,10,P,*";  
      String tokens[20];

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
        
      for(int i = 1; i < 10; i ++){
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
        if(value == "*"){
          break;
         }
        tokens[i] = value;//.toInt();  
        
//        Serial.print(tokens[i]);
        Serial.print(" \n");
      }
      Serial.print("breaks");
//validate tokens 
for(int j = 0; j < 10; j++){
  Serial.print(tokens[j]);
}
      
      //load alternate values into the arrays 
      

delay(10000);
}


   
//
//
//printf("array size %d\n", arr_size);
//
//int index;
//printf("canister: [");
//for( index = 0; index <arr_size; index++){
//        printf( "%s,", canister[index] );
//   }
//        printf( "]\n" );
//printf("ref_weight: [");
//for( index = 0; index <arr_size; index++){
//        printf( "%s,", ref_weight[index] );
//   }
//       Serial.print( "]\n" );


char** str_split(char* a_str, const char a_delim){
//      Serial.write(a_str);
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
