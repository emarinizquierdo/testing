#include <Arduino.h>
#include "configuration.h"
#include "light.h"

void setup() {

  config();

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(10000);
  checkForUpdates();

  hot(random(1024));
  delay(10000);
  rain(random(1024));
  delay(10000);
  wind(random(1024));

}