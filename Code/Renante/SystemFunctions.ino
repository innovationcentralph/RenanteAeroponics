void readSensors(){

  digitalWrite(SYSTEM_LED, HIGH);
  
  /* --------------- Read Temnperature Sensor --------------- */
  DS18B20.requestTemperatures();
  float tempC = DS18B20.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) {
    Sensors.Temperature = String(tempC, 2);
  }else{
    Sensors.Temperature = "ERROR";
  }

  /* --------------- Read PH Sensor --------------- */
  int phRaw = analogRead(PH_PIN);

  // Convert sensor value to millivolts
  float millivolts = phRaw * (3300.0 / 4095.0);
  
  // Convert millivolts to pH using 2 point slope formula
  float phValue = (0.0083432657926103 * millivolts) - 1.6388557806913;  // Please update formula

  Sensors.PH = String(phValue, 2);
  

  /* --------------- Read Turbidity Sensor --------------- */
  int turbidityRaw = analogRead(TURBIDITY_PIN);
 
  int turbidity = map(turbidityRaw, 0, 4095, 0, 3000);                  // Please update max Values

  Sensors.Turbidity = String(turbidity);
  
  digitalWrite(SYSTEM_LED, LOW);
  
}
