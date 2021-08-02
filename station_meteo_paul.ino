/* programme de pilotage d'une mini station météo
 *  équiupée avec un BM280, capteur de température, pressiopn, humidité 
 *  on utilise un afficheur LCD 16 car * 2 li 
 *  Le port série est utilisé pour debugger le programme
 *  la communication entre les différents éléments se fait via I2C
 *  les bibliotheques BM280 et liquide_crystal sont inclues dans
 *  le programme
 *  Ce programme a été réalisé le 22/07/2021 par Paul et Jacques
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>

//declaration ecran lcde
LiquidCrystal_I2C lcd(0x27,16,2); 

//définition des ports SPI pour le BM280
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

// pression au niveau de la mer
#define SEALEVELPRESSURE_HPA (1013.25)

// declaration capteur temp,pression,humidité ici on utilise une liaison I2C
//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // sélection SPI
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// variable définissant le temps d'attente avant lecture des données
 int delayTime = 5000;
 float tempe = 0;
 float pression = 0;
 float humi = 0;
 float alti = 0;
 
//INIT
void setup() {
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();
 lcd.setCursor(2,0);
 lcd.print("Salut Paulo!");
 lcd.setCursor(0,1);
 lcd.print("Station meteo...");

//Serial.println("je suis dans le setup !");
delay(3000);
// while(!Serial);    // time to get serial running
// Serial.println(F("BME280 test"));
 unsigned status;

///* TEST I2C
// * 
 status = bme.begin(); 
   if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); 
        Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }

 Serial.println("-- Default Test --");
//*/
}

void loop() {
    //Serial.println("je suis dans la loop !");
    readValues();
    printValues();
    delay(delayTime);
    
} 
void readValues(){
  //Serial.println("je suis dans le readValuesz !");
  tempe = bme.readTemperature();
  pression = bme.readPressure() / 100.F;
  humi = bme.readHumidity();
  alti = bme.readAltitude(SEALEVELPRESSURE_HPA); 
  //Serial.println("temp= "+String(tempe));
  delay(500);
}

void printValues() {
//ecriture des valeurs du capteur sur le LCD
//  lcd.backlight();
//  Serial.println("je suis dans printValues !");
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(String(tempe));
  lcd.setCursor(10,0); 
  lcd.print(" C");
 // affichage humidité  
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Humidite: ");
  lcd.setCursor(10,1);
  lcd.print(String(humi));
  lcd.setCursor(14,1); 
  lcd.print("%");

  delay(5000);
 // affichage suivant pression et altitude
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Press:");
  lcd.setCursor(6,0);
  lcd.print(String(pression));
  lcd.setCursor(12,0); 
  lcd.print("mbar");
 // affichage humidité  
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Altitude: ");
  lcd.setCursor(9,1);
  lcd.print(String(alti));
  lcd.setCursor(14,1); 
  lcd.print("m");

 
   
 // controle moniteur série
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println("; °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
   
}
