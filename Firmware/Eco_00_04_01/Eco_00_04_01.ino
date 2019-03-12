#include <SPI.h>
#include <SD.h>
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <Adafruit_SHT31.h>
#include <Ethernet.h>

#include "ChronoSettings.h"
#include "SensorSettings.h"
#include "NetworkSettings.h"
#include "FileSettings.h"

const int chipSelect = 4;

void setup()
{
  pinMode(47,OUTPUT);
  digitalWrite(47,LOW);
  delay(500);
  digitalWrite(47,HIGH);
  //Serial.begin(9600);
  //Serial.println("Setup Start");
  //Serial.println();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  pinMode(A10, OUTPUT);
  pinMode(A11, OUTPUT);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
  digitalWrite(A9, LOW);
  digitalWrite(A10, LOW);
  digitalWrite(A11, LOW);
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (!SD.begin(chipSelect)) {
    return;
  }
  config_networkParameters(networkConfigFileName); //passes the file name !!!!!!!
  config_delayParameters(delayConfigFileName);
  delay(1000);
  card_readSensorLocation(sensorsFolder);
  config_sensorPrevAssigned(assignedSensorsFileName);
  config_alarms(alarmsFolder);
  //Ethernet.begin(macAddress_, ipAddress_, dnsAddress_, gatewayAddress_);
  Ethernet.begin(macAddress_, ipAddress_);
  sht31.begin(0x44);
  sht31.heater(false);
  server.begin();
  //debug_setupprinter();
  //Serial.println("Setup End");
  //Serial.println();
}

void loop()
{
  html_interface();
  if (chrono_trigger())
  {
    data_write("data");
  }
  alarm_watchdog();
}


