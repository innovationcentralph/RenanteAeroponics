#define PH_PIN           32
#define TEMP_PIN         33
#define TURBIDITY_PIN    35

#define RELAY_TEMP_HIGH  12
#define RELAY_TEMP_LOW   14
#define RELAY_PH_HIGH    27
#define RELAY_PH_LOW     26
#define RELAY_FEEDER     25
#define RELAY_PUMP       13

#define SYSTEM_LED       23
#define WIFI_LED         19

#define FLOAT_EMPTY      34
#define FLOAT_FULL       39

#define ON  LOW
#define OFF HIGH

#define DS3231_I2C_ADDRESS 0x68


struct Sensors{
  String PH;
  String Temperature;
  String Turbidity;
}Sensors;
