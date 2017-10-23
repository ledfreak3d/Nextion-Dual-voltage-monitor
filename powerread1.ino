#include <Wire.h>
#include <Adafruit_INA219.h>
#include "Nextion.h"
#include <ESP8266WiFi.h>


char volts[10] = {0};
char amps[10] = {0};
char watts[10] = {0};

char voltsb[10] = {0};
char ampsb[10] = {0};
char wattsb[10] = {0};


SoftwareSerial nextion(13, 15);

Adafruit_INA219 ina219(0x40);
Adafruit_INA219 ina219b(0x41);

Nextion myNextion(nextion, 115200);

void setup()
{
 uint32_t currentFrequency;

 Serial.begin(9600);
 myNextion.init();
 Serial.println("Init Nextion");
 
 Serial.println("Measuring voltage and current with INA219 ...");
 ina219.begin();
  ina219b.begin();
 //pinMode(2,OUTPUT);
}

void loop()
{

 float shuntvoltage = 0;
 float busvoltage = 0;
 float current_mA = 0;
 float loadvoltage = 0;
 float power = 0;

  float shuntvoltageb = 0;
 float busvoltageb = 0;
 float current_mAb = 0;
 float loadvoltageb = 0;
 float powerb = 0;
///  Channel A ////////////////////////////////

 shuntvoltage = ina219.getShuntVoltage_mV();
 busvoltage = ina219.getBusVoltage_V();
 current_mA = ina219.getCurrent_mA();
 loadvoltage = busvoltage + (shuntvoltage / 1000);
 power = current_mA * loadvoltage;

/////// Channel b /////////////////////////////

   shuntvoltageb = ina219b.getShuntVoltage_mV();
 busvoltageb = ina219b.getBusVoltage_V();
 current_mAb = ina219b.getCurrent_mA();
 loadvoltageb = busvoltageb + (shuntvoltageb / 1000);
 powerb = current_mAb * loadvoltageb;
  
  
  
  double dVal = busvoltage;
    char volts[10];
    dtostrf(dVal, 5, 3, volts);  // Prints "123.46"
//    Serial.println(volts);

 double dVal1 = current_mA;
    char amps[10];
    dtostrf(dVal1, 5, 3, amps);  // Prints "123.46"
//    Serial.println(amps);

     double dVal2 = power;
    char watts[10];
    dtostrf(dVal2, 5, 3, watts);  // Prints "123.46"
 //   Serial.println(watts);

////////// Cannel 2 calc ///////////////////

double dVal3 = busvoltageb;
    char voltsb[10];
    dtostrf(dVal3, 5, 3, voltsb);  // Prints "123.46"
//    Serial.println(volts);

 double dVal4 = current_mAb;
    char ampsb[10];
    dtostrf(dVal4, 5, 3, ampsb);  // Prints "123.46"
//    Serial.println(amps);

     double dVal5 = powerb;
    char wattsb[10];
    dtostrf(dVal5, 5, 3, wattsb);  // Prints "123.46"


myNextion.setComponentText("t0", String(volts));
myNextion.setComponentText("t1", String(amps));
myNextion.setComponentText("t2", String(watts));
myNextion.setComponentText("t8", String(voltsb));
myNextion.setComponentText("t9", String(ampsb));
myNextion.setComponentText("t10",String(wattsb));

}

