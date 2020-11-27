#include <Arduino.h>
#include "configuration.h"
#include "light.h"
#include "forecast.h"


unsigned long previousUPDATEMillis = 0;
unsigned long previousFORECASTMillis = 0;

// constants won't change :
// UPDATEInterval = every 24 hours
const long UPDATEInterval = 24 * 3600000;
const long FORECASTInterval = 1800000;

void setup() {

  config();
  checkForUpdates();
  getForecast();

}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long currentMillis = millis();

  if (currentMillis - previousUPDATEMillis >= UPDATEInterval) {
    previousUPDATEMillis = currentMillis;
    checkForUpdates();
    Serial.print( "OUT OF checkForUpdates " );
  }

  if (currentMillis - previousFORECASTMillis >= FORECASTInterval) {
    previousFORECASTMillis = currentMillis;
    getForecast();
    Serial.print( "OUT OF getForecast " );
  }



}