#ifndef WIFI_h
#define WIFI_h

#include <Arduino.h>
#include <WiFi.h>


class Wifi{
  
  private:
    const char* SSID;
    const char* PASSWORD;

  public:
    Wifi(const char* ssid, const char* password);
    
    void connect(); 
    bool isConnected();
    void setSSID(const char *ssid);
    void setPass(const char *pass);
    
};

#endif
