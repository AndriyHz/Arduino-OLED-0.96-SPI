#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include "HCuOLED.h"
//#include <Digital_Light_TSL2561.h>
#include "SoftwareSerial.h"
/* Digital pin number for the displays chip select pin */
#define CS_DI 10
/* Digital pin number for the displays data/command pin */
#define DC_DI 9
/* Digital pin number for the displays reset pin */
#define RST_DI 8

HCuOLED HCuOLED(SH1106, CS_DI, DC_DI, RST_DI); // For SH1106 displays (HCMODU0058 & HCMODU0059)
//float light;

// O2 Sensor 
#define Version     11          // version, 1.0 or 1.1, which depands on your board you use as it is
const int pinO2     = A3;       // Connect Grove - Gas Sensor(O2) to A0
#if Version==11
const int AMP   = 121;
#elif Version==10
const int AMP   = 201;
#endif
const float K_O2    = 7.43;
 
BME280 capteur;
 
void setup() {
 HCuOLED.Reset();
   Serial.begin(9600);
   //TSL2561.init();
  while (!Serial) {
    // Attente de l'ouverture du port série pour Arduino LEONARDO
  }
  //configuration du capteur
  capteur.settings.commInterface = I2C_MODE; 
  capteur.settings.I2CAddress = 0x76;
  capteur.settings.runMode = 3; 
  capteur.settings.tStandby = 0;
  capteur.settings.filter = 0;
  capteur.settings.tempOverSample = 1 ;
  capteur.settings.pressOverSample = 1;
  capteur.settings.humidOverSample = 1;
 
 // Serial.println("Starting BME280... ");
 // delay(10);  // attente de la mise en route du capteur. 2 ms minimum
  // chargement de la configuration du capteur
  capteur.begin();
}
 
void loop() {
  // O2
    float sensorValue;
    float sensorVoltage;
    float Value_O2;
    sensorValue   = analogRead(pinO2);
    sensorVoltage =(sensorValue/1024.0)*3.25;
    sensorVoltage = sensorVoltage/(float)AMP*10000.0;
    Value_O2 = sensorVoltage/K_O2;

    /* Read the current value*/
  // light = TSL2561.readVisibleLux();
   //delay(100);

     // DISPLEY //
    /* Write the value to the display buffer */
    HCuOLED.Erase(0,0,128,64);
    //HCuOLED.SetFont(LCDLarge_24pt );
    //HCuOLED.SetFont(Terminal_8pt);
    HCuOLED.Cursor(20,0);
    HCuOLED.Print("%");
    HCuOLED.Cursor(0,0);\
    HCuOLED.Print("O2");
    HCuOLED.Cursor(40,0);
    HCuOLED.Print(Value_O2, 3);

    //HCuOLED.Cursor(100,10);
    //HCuOLED.Print("lux");
    //HCuOLED.Cursor(90,0);
    //HCuOLED.Print(light, 3, 0);

       
    //HCuOLED.SetFont(MedProp_11pt);
   // HCuOLED.Cursor(0,49);
    HCuOLED.Cursor(0,20);
    HCuOLED.Print("Temp");
    HCuOLED.Cursor(40,20);
    HCuOLED.Print(capteur.readTempC());
    HCuOLED.Cursor(0,40);
    HCuOLED.Print("Hum");
    HCuOLED.Cursor(40,40);
    HCuOLED.Print(capteur.readFloatHumidity());
    HCuOLED.Cursor(70,40);
    HCuOLED.Print("Press");
    HCuOLED.Cursor(70,49);
    HCuOLED.Print(capteur.readFloatPressure(), 2);
    delay(1000);   
       
    /* Output the display buffer to the screen */
    HCuOLED.Refresh();
  
 /*   
  Serial.print("Température: ");
  Serial.print(capteur.readTempC(), 2);
  Serial.print(" °C");
  Serial.print("\t Pression: ");
  Serial.print(capteur.readFloatPressure(), 2);
  Serial.print(" Pa");
  Serial.print("\t humidité relative : ");
  Serial.print(capteur.readFloatHumidity(), 2);
  Serial.println(" %");
  delay(1000);
 */
}
