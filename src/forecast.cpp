#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include "light.h"

const char* forecastBaseURL = "http://thedropcubecom.appspot.com/forecasts/2715387";
const char* forecastFingerPrint = "31 2D 13 36 0A E6 25 4E A9 F3 A2 0E 2D C3 79 AF 92 DA 33 EC";

void getForecast() {
  String URL = String( forecastBaseURL );

  Serial.println( URL );

  HTTPClient httpClient;
  httpClient.begin( URL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {

    String forecastCode = httpClient.getString();
    int x = forecastCode.toInt();

    Serial.print( "Forecast code: " );
    Serial.println( forecastCode );

    if (x == 800){
      hot(1023);
      Serial.print( "HOT " );
    }
    
    if ( 200 <= x && x <= 531 ){
      rain(x * 1.5);
      Serial.print( "RAIN " );
    }

  }
  else {
    Serial.print( "FORECAST NOT AVAILABLE " );
    Serial.println( httpCode );
  }
  httpClient.end();
}