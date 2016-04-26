#define loadcell A1
unsigned int lc_value;

void setup() {
  // put your setup code here, to run once:
  pinMode(loadcell, INPUT); //declare pin 25 as input
  Serial.begin(9600); // ser the baud rate od the serial monitor
  Serial.print("value");
  Serial.print("\tVoltage"); //"t" create spacing of a tab
  Serial.println("\tWeight"); // like above
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  unsigned int lcv[49];

  lc_value  =  analogRead(loadcell); // take reading from sensor
  delay(1);
  
  for (int i = 1; i < 50; i++)
  {
    lcv[i] = analogRead(loadcell);
    lc_value = lc_value+ lcv[i];
    delay(5);
  }

  lc_value = lc_value / 50;

  float lc_raw_voltage = lc_value * 0.0048828125 + 0.013;//convert analog value to voltage
  float lc_weight_value = lc_raw_voltage * 1134 - 567; //convert voltage value to the weigt value, parameter a and b needed.
  Serial.print(lc_value); // display the analog value in serial monitor
  Serial.print("\t");
  Serial.print(lc_raw_voltage,3); // display the voltage value in serial monitor
  Serial.print("\t");
  Serial.println(lc_weight_value); // display the weight value in the serial monitor
}
