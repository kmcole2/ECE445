/*

   LCD-Arduino Connections
   Analog Pin 4 (A4 to SDA) ATMega328 PIN 28
   Analog Pin 5 (A5 to SCI) ATMega328 PIN 27

   GM-Arduino Connections
   Analog Pin 10, ATMega PIN 16
   Analog Pin 11, ATMega PIN 17

   RLY-Arduino Connections
   Analog Pin 6, ATMega PIN 12
   Analog Pin 5, ATMega PIN 11

   http://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight
   frequency
   https://code.google.com/archive/p/arduino-pwm-frequency-library/downloads
*/

#include "PWM.h"
#include <Wire.h>
#include "rgb_lcd.h"

#define irsensor A0
#define loadcell A2

float ir_value;
float ir_border = 915;      // need definition for distance
float lc_value;

float m1, m2, m3, m4 = 0;
int c1 = 0;
int ss = 0;
boolean irir;

float task[7] = {1, 10, 1, 3, 300, -1};
int ctr = 0;

/*PWM signal*/
int GMC1_PWM = 10;  //PIN 16 CONTAINER #1
int GMC2_PWM = 11;  //PIN 17 CONTAINER #2

int GMC1_GND = 12;  //PIN 18 CONTAINER #1
int GMC2_GND = 13;  //PIN 19 CONTAINER #2

int RLY3 = 5;       //PIN 11 CONTAINER #3
int RLY4 = 6;       //PIN 12 CONTAINER #4


rgb_lcd lcd;

void setup() {

  //   PIN SETTING
  pinMode(GMC1_PWM, OUTPUT);
  pinMode(GMC2_PWM, OUTPUT);
  pinMode(GMC1_GND, OUTPUT);
  pinMode(GMC2_GND, OUTPUT);

  pinMode(RLY3, OUTPUT);
  pinMode(RLY4, OUTPUT);

  //   LCD Initialization
  lcd.begin(16, 2);               // set up the LCD's number of columns and rows:
  lcd.print("INGREDIENT");  // Print a message to the LCD.
  lcd.setCursor(0, 1);            // Move cursor to second line
  lcd.print("PRINTER");  // Print on second line
  lcd.display();

  //   PWM Initialization
  analogWrite(GMC1_PWM, 0);
  analogWrite(GMC2_PWM, 0);

  //   RELAY Initialization
  digitalWrite(RLY3, LOW);
  digitalWrite(RLY4, LOW);

  //   IR SENSOR Initialization
  pinMode(irsensor, INPUT); //declare pin A0 as input

  //   LOAD CELL Initialization
  pinMode(loadcell, INPUT); //declare pin A2 as input

  // PRESET THE VALUE for test purpose ONLY

  digitalWrite(GMC1_GND, LOW);
  digitalWrite(GMC1_GND, LOW);

  m1 = 20;
  c1 = 1;
  delay(3000);
}



void loop()
{

  if (ss == 0)
  {
    irir = irsensoring();
    displaying();
    delay(5000);
    ss = 1;
  }
  else if (ss == 1)
  {
    // read the task from array
    c1 = task[ctr];
    ctr++;
    m1 = task[ctr];

    //initializing screen
    lcd.clear();
    lcd.setCursor(0, 0);
    if (c1 == 1)
    {
      lcd.print("BAKING SODA");
    }
    else if (c1 == 2)
    {
      lcd.print("SUGAR");
    }
    else if (c1 == 3)
    {
      lcd.print("WATER");
    }
    else if (c1 == 4)
    {
      lcd.print("MILK");
    }
    lcd.setCursor(0, 1);
    lcd.print(m1, DEC);


    //start dispensing process
    m4 = loadcelling();
    delay(3000);

    while (ss == 1)
    {
      m3 = loadcelling();
      m2 = m3 - m4;
      irir = irsensoring();
      dispensing();
      displaying();
    }
  }
  else if (ss == 2)
  {
    displaying();
    delay(3000);
    ctr++;
    if (task[ctr] == 1)
    {
      ss = 3;
      ctr++;
    }
    else if (task[ctr] == 0)
    {
      ss = 1;
      ctr++;
    }
    else if (task[ctr] < 0)
    {
      ss = 4;
      
    }
  }
  else if (ss == 3)
  {
    displaying();
    while (irir == 1)
    {
      irir = irsensoring();
    }
    displaying();
    delay(3000);
    while (irir == 0)
    {
      irir = irsensoring();
    }
    delay(3000);
    ss = 1;
  }
  else if (ss == 4)
  {
    displaying();
    delay(3000);
//    ss = 0;
  }

}

void dispensing()      // -----DISPENSING MODULE-----
{
  if ((irir == 1) && (ss == 1))
  {
    if (c1 == 1) // if we are dispensing dry ingredient 1
    {
      if ( m2 < m1 )
      {
        analogWrite(GMC1_PWM, 255);
      }
      else if (m2 >= m1 )
      {
        analogWrite(GMC1_PWM, 0);
        ss = 2;
      }
    }
    if (c1 == 2)      // if we are dispensing dry ingredient 2
    {
      if ( m2 < m1 )
      {
        analogWrite(GMC2_PWM, 255);
      }
      else
      {
        analogWrite(GMC2_PWM, 0);
        ss = 2;
      }
    }
    if (c1 == 3)      // if we are dispensing wet ingredient 3
    {
      if ( m2 < m1 )
      {
        digitalWrite(RLY3, HIGH);
      }
      else
      {
        digitalWrite(RLY3, LOW);
        ss = 2;
      }
    }
    if (c1 == 4)      // if we are dispensing wet ingredient 4
    {
      if ( m2 < m1 )
      {
        digitalWrite(RLY4, HIGH);
      }
      else
      {
        digitalWrite(RLY4, LOW);
        ss = 2;
      }
    }
  }
  else
  {
    analogWrite(GMC1_PWM, 0);
    analogWrite(GMC2_PWM, 0);
    digitalWrite(RLY3, LOW);
    digitalWrite(RLY4, LOW);

    delay(3000);
  }

  return;
}

boolean irsensoring()      //-----IR SENSOR MODULE-----
{
  float sample1 = 0;
  ir_value = analogRead(irsensor);      //take reading from sensor

  for (int i = 1; i < 10; i++)
  {
    sample1 = analogRead(irsensor);
    ir_value = ir_value + sample1;
    delay(1);
  }
  ir_value = ir_value / 10;

  if (ir_value > ir_border)
  {
    return 0;
  }
  else
  {
    return 1;
  }

}

float loadcelling()     //-----LOAD CELL MODULE-----
{
  float sample;
  float weight;

  lc_value  =  analogRead(loadcell);      // take reading from sensor
  delay(1);

  for (int i = 1; i < 1000; i++)
  {
    sample = analogRead(loadcell);
    lc_value = lc_value + sample;
    delay(0.5);
  }
  lc_value = lc_value / 1000;     // calculat the average value for the 1000 sample to increase stability

  weight = lc_value * 0.00488 + 0.013;//convert analog value to voltage

  weight = (weight - 0.7) * 1111.111111;

  return weight;
}

void displaying()
{
  if (irir == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PAUSED");
    lcd.setCursor(0, 1);
    lcd.print("NEED CONTAINER");
  }
  else if ((irir == 1) && (ss == 0))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WAITING FOR");
    lcd.setCursor(0, 1);
    lcd.print("RECIPE");
  }

  else if ((irir == 1) && (ss == 1))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DISPENSING");
    lcd.setCursor(0, 1);
    lcd.print("#");
    lcd.setCursor(1, 1);
    lcd.print(c1);
    lcd.setCursor(3, 1);
    lcd.print(m2, DEC);
  }
  else if ((irir == 1) && (ss == 2))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DISPENSED");
    lcd.setCursor(0, 1);
    lcd.print("#");
    lcd.setCursor(1, 1);
    lcd.print(c1);
    lcd.setCursor(3, 1);
    lcd.print(m2, DEC);
  }
  else if ((irir == 1) && (ss == 3))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PAUSED");
    lcd.setCursor(0, 1);
    lcd.print("REMOVE CONTAINER");

  }
  else if ((irir == 1) && (ss == 4))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RECIPE");
    lcd.setCursor(0, 1);
    lcd.print("COMPLETE");

  }
}

























