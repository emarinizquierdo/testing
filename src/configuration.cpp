#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiManager.h>
#include <Arduino.h>
#include "light.h"

const int FW_VERSION = 1252;
const char* baseURL = "https://raw.githubusercontent.com/emarinizquierdo/testing/master/fota/";
const char* fingerPrint = "70 94 DE DD E6 C4 69 48 3A 92 70 A1 48 56 78 2D 18 64 E0 B7";
const int led = 13;



void config(){

  configureLights();

  Serial.begin(115200);
 
  // Creamos una instancia de la clase WiFiManager
  WiFiManager wifiManager;
 
  // Descomentar para resetear configuración
  // wifiManager.resetSettings();
 
  // Cremos AP y portal cautivo
  wifiManager.autoConnect("ESP8266Temp");
 
  Serial.println("Ya estás conectado");

}

void checkForUpdates() {
  String fwURL = String( baseURL );
  String fwVersionURL = fwURL;
  String noCache = String(random(10000));

  fwVersionURL.concat( "version?nc=" );
  fwVersionURL.concat( noCache );

  Serial.println( "Checking for firmware updates." );
  Serial.print( "Firmware version URL: " );
  Serial.println( fwVersionURL );

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL, fingerPrint);
  httpClient.addHeader("Cache-Control", "max-age=0", true);
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );

    int newVersion = newFWVersion.toInt();

    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );

      String fwImageURL = fwURL;
      fwImageURL.concat( newFWVersion );
      fwImageURL.concat( ".bin" );

      Serial.print( "Firmware URL: " );
      Serial.println( fwImageURL );
      t_httpUpdate_return ret = ESPhttpUpdate.update( fwImageURL, "",  fingerPrint );

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;
      }
    }
    else {
      Serial.println( "Already on latest version" );
    }
  }
  else {
    Serial.print( "Firmware version check failed, got HTTP response code " );
    Serial.println( httpCode );
  }
  httpClient.end();
}