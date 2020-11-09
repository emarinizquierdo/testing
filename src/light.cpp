#include <Arduino.h>

//RAINBOW CONSTANTS
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      1000    //Rest Between Inhalations.

//STORM CONSTANTS
#define BETWEEN 30000
#define DURATION 200
#define TIMES 20

unsigned long lastTime = 0;
int waitTime = 0;

const int RED = D2;
const int GREEN = D4;
const int BLUE = D5;
const int GROUND = D3;

//Control vars
unsigned int modeNextTime = 0;
String modeValue = "NORMAL";
int hotValue;
int windValue;
int rainValue;
int snowValue;
bool stormValue;

//Rainbow vars
long value3;
long value2;
long value1;
long current_value3;
long current_value2;
long current_value1;
int x;

void configureLights(){

  pinMode(RED, OUTPUT);   // LED pin as output.
  pinMode(GREEN, OUTPUT);   // LED pin as output.
  pinMode(BLUE, OUTPUT);   // LED pin as output.
  pinMode(GROUND, OUTPUT);

  digitalWrite(GROUND, HIGH);

}

//Storm control
void storm(){

  if (millis() - waitTime > lastTime)  // time for a new flash

    {
      // adjust timing params
      lastTime += waitTime;
      waitTime = random(BETWEEN);

      for (int i=0; i< random(TIMES); i++)
      {
        Serial.println(millis());
        analogWrite(RED, 439);
        analogWrite(GREEN, 1);
        analogWrite(BLUE, 1);
        delay(20 + random(DURATION));
        analogWrite(RED, 1023);
        analogWrite(GREEN, 1023);
        analogWrite(BLUE, 1023);
        delay(10);
      }
    }

}

//Hot control
void hot(int value){
  value = 1023 - value;
  analogWrite(RED, value);
  analogWrite(GREEN, 1023);
  analogWrite(BLUE, 1023);
}

//Rain control
void rain(int value){
  value = 1023 - value;
  analogWrite(RED, 1023);
  analogWrite(GREEN, 1023);
  analogWrite(BLUE, value);
}

//Snow control
void snow(int value){
  value = 1023 - value;
  analogWrite(RED, 950 - ((1023 - value) / 2));
  analogWrite(GREEN, value);
  analogWrite(BLUE, value);
}

//Wind control
void wind(int value){
  value = 1023 - value;
  analogWrite(RED, 1);
  analogWrite(GREEN, 250);
  analogWrite(BLUE, 1023);
}

//Rainbow control
void rainbow(){

  x = random(3, 9);

  if (value1 > current_value1){
    current_value1++;
    analogWrite(RED, current_value1);
    delay(x);
  }

  if (value1 < current_value1){
    current_value1--;
    analogWrite(RED, current_value1);
    delay(x);
  }

  if (value1 == current_value1){
    analogWrite(RED, current_value1);
    value1 = random(1023);
  }

  //////////////////////////

  if (value2 > current_value2){
    current_value2++;
    analogWrite(GREEN, current_value2);
    delay(x);
  }

  if (value2 < current_value2){
    current_value2--;
    analogWrite(GREEN, current_value2);
    delay(x);
  }

  if (value2 == current_value2){
    analogWrite(GREEN, current_value2);
    value2 = random(1023);
  }

  ///////////////////////////////

  if (value3 > current_value3){
    current_value3++;
    analogWrite(BLUE, current_value3);
    delay(x);
  }

  if (value3 < current_value3){
    current_value3--;
    analogWrite(BLUE, current_value3);
    delay(x);
  }

  if (value3 == current_value3){
    analogWrite(BLUE, current_value3);
    value3 = random(1023);
  }

}