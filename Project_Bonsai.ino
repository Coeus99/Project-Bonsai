#include <SD.h>
#include <SPI.h>
#include <TFT.h>
#include <Wire.h>
#include "I2CSoilMoistureSensor.h"

#define CS   10
#define DC   9
#define RESET  8

TFT screen = TFT(CS, DC, RESET);
File dataFile;
I2CSoilMoistureSensor sensor(0x20);

void setup() {
  //Begin and wait for serial port to respond
  Serial.begin(9600);
  while(!Serial){
    ;
  }

  //Initialize SD card to pin 4
  Serial.print("Initializating SD card...");
  if (!SD.begin(4)) {
    Serial.print("initialization failed");
    return;
  }
  Serial.println("initialization done.");

  //Remove old file
  SD.remove("bonsai.csv");
  if(SD.exists("baonsai.csv")){
    ;
  } else {
    Serial.println("Successfully old removed file.");
  }
  
  //Create data file
  Serial.println("Creating bonsai.csv...");
  dataFile = SD.open("bonsai.csv", FILE_WRITE);
  dataFile.close();
  if (SD.exists("bonsai.csv")) {
    Serial.println("Successfully created bonsai.csv.");
  } else {
    Serial.println("Failed to create bonsai.csv.");
    return;
  }

  //Begin screen object
  Wire.begin();
  screen.begin();
  screen.setTextColor(0x07FF);
  screen.setTextSize(1);
  sensor.begin(1);
}

void loop() {
  //Read data from sensor
  int soilCapacitance = sensor.getCapacitance();
  unsigned int lightLevel = sensor.getLight(true);
  float temperature = sensor.getTemperature() / 10.0;
  sensor.sleep();

  //Write to datafile
  Serial.println("Writing to file...");
  dataFile = SD.open("bonsai.csv",FILE_WRITE);
  dataFile.print(soilCapacitance);
  dataFile.print(",");
  dataFile.print(lightLevel);
  dataFile.print(",");
  dataFile.print(temperature,1);
  dataFile.print("\n");
  dataFile.close();
  Serial.println("Finished.");

  //Print to LCD screen
  screen.setCursor(0,0);
  screen.fillScreen(0x0000);
  screen.print("Soil Capacitance: ");
  screen.println(soilCapacitance);
  screen.print("Light Level: ");
  screen.println(lightLevel);
  screen.print("Temperature: ");
  screen.print(temperature,1);
  screen.print(" C");
  
  delay(5000);
}
