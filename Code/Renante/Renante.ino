#include "SystemConfig.h"
#include "UserConfig.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Wifi.h"
#include "HTTPSClient.h"
#include "Wire.h"


// Instance creation
Wifi Wifi(WIFI_SSID, WIFI_PASS); 
HTTPSClient HTTPSClient;

OneWire oneWire(TEMP_PIN);
DallasTemperature DS18B20(&oneWire);

// Global variables
unsigned long int sensorReadMillis = 0;
unsigned long int webDatalogMillis = 0;
unsigned long int currentMillis    = 0;
unsigned long int feederStartMillis = 0;

byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

bool feederStarted = false;




void setup() {
  Serial.begin(9600);

  /* Connect to configured wifi */
  Wifi.connect();

  /* initialize RTC */
  Wire.begin();

  /* initialize Temperature Sensor */
  DS18B20.begin();
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(30,42,16,5,13,10,16);

  
  /* initialize hardware components */
  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(RELAY_FEEDER, OUTPUT);
  pinMode(RELAY_PH_LOW, OUTPUT);
  pinMode(RELAY_PH_HIGH, OUTPUT);
  pinMode(RELAY_TEMP_LOW, OUTPUT);
  pinMode(RELAY_TEMP_HIGH, OUTPUT);

  pinMode(SYSTEM_LED, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);

  pinMode(FLOAT_EMPTY, INPUT);
  pinMode(FLOAT_FULL,  INPUT);

  digitalWrite(RELAY_PUMP, OFF);
  digitalWrite(RELAY_FEEDER, OFF);
  digitalWrite(RELAY_PH_LOW, OFF);
  digitalWrite(RELAY_PH_HIGH, OFF);
  digitalWrite(RELAY_TEMP_LOW, OFF);
  digitalWrite(RELAY_TEMP_HIGH, OFF);

  digitalWrite(SYSTEM_LED, LOW);
  digitalWrite(WIFI_LED, LOW);

  sensorReadMillis = millis();
  webDatalogMillis = millis();
  currentMillis    = millis();
  
}

void loop() {

  /* Read Sensors every X time */
  if(millis() - sensorReadMillis > SENSOR_READ_INTERVAL){
    readSensors();
    sensorReadMillis = millis();
  }

   /* Send dtaalog to web every X time */
  if(millis() - webDatalogMillis > WED_DATALOG_INTERVAL){
    if (Wifi.isConnected()) {
      Serial.println("SENDING DATALOG TO WEB");
      webDatalogMillis = millis();
    }
  }

  /* Check Tank Status */
  if(digitalRead(FLOAT_EMPTY) == HIGH){
    /* Turn ON Refill Pump */
    digitalWrite(RELAY_PUMP, ON);
  }
  if(digitalRead(FLOAT_FULL) == HIGH){
    /* Turn ON Refill Pump */
    digitalWrite(RELAY_PUMP, OFF);
  }

  /* Check feeding time */
  if(millis() - currentMillis > 1000){
    readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

    if (hour == FEEDER_TIME_1 || hour == FEEDER_TIME_2) {
      if(feederStarted == false){
        feederStarted = true;
        feederStartMillis = millis();
      } 
    }
    else{
      feederStarted = false;
    }
    
    currentMillis = millis();
  }

  if(feederStarted){
    if(millis() - feederStartMillis < FEEDER_DURATION){
      digitalWrite(RELAY_FEEDER, ON);
    }
    else{
      digitalWrite(RELAY_FEEDER, OFF);
    }
  }
  
  

  
  

}
