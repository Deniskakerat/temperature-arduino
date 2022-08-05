#include <SPI.h>
#define MAX6675_SO  12
#define MAX6675_SCK  13
int MAX6675_CS[3]={8,9,10};
void setup() 
{
  Serial.begin(9600);
  Serial.println("current\n");
}
void loop() {
  float temperature_read1=readThermocouple(2);   
  float temperature_read2=readThermocouple(1);   
  float temperature_read3=readThermocouple(0);   
  Serial.print(temperature_read1, 2);
  Serial.print(" , ");
  Serial.print(temperature_read2, 2);
  Serial.print(" , ");
  Serial.print(temperature_read3, 2);
   Serial.print("\n");
  delay(1000);   
}
double readThermocouple(int number) {
  uint32_t v;
  pinMode(MAX6675_CS[number], OUTPUT);
  pinMode(MAX6675_SO, INPUT);
  pinMode(MAX6675_SCK, OUTPUT);
  
  digitalWrite(MAX6675_CS[number], LOW);
  delay(1);
  v = shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  v <<= 8;
  v |= shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  digitalWrite(MAX6675_CS[number], HIGH);
  if (v & 0x4) 
  {    
    // Bit 2 indicates if the thermocouple is disconnected
    return NAN;     
  }
    v >>= 3;
  return v*0.25;
 return v;
}
