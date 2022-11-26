#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "LedBlinker.h"

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

LedBlinker Blinker;

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(A1);
DallasTemperature tempSensors(&oneWire);

float minTemperature = 32767;
float maxTemperature = -32768;

void initLed(){
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    Blinker.init(LED_GREEN, 500, 1000);
    turnOffLed();
}

void turnOffLed(){
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
}

void initButtons(){
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void initLCD(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void printLCD(float tempIn, float tempOut){
    char buffer[40];
    lcd.clear();

    sprintf(buffer, "TEMP. OUT%6s", String(tempOut, 2).c_str());
    lcd.setCursor(0, 0);
    lcd.print(buffer);

    sprintf(buffer, "TEMP. IN%7s", String(tempIn, 2).c_str());
    lcd.setCursor(0, 1);
    lcd.print(buffer);

    
}

void printMAX(float tempMax){
    char buffer[40];
    sprintf(buffer, "MAX%6s", String(tempMax, 2).c_str());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(buffer);
}

void printMIN(float tempMin){
    char buffer[40];
    sprintf(buffer, "MIN%6s", String(tempMin, 2).c_str());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(buffer);
}

void printWarning(float tempOut){
    char buffer[40];
    sprintf(buffer, "GORACO%6s", String(tempOut, 2).c_str());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(buffer);
}

void actionBasedOnTemperature(float current){
    if(current < 25.5){
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, HIGH);
    }else if(current < 27 && current >= 25.5){
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
        Blinker.runMeInLoop();
    }else if(current >= 27){
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
        printWarning(current);
    }else {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
    }
}

void setup(){
    tempSensors.begin();  
    initLCD();
    initLed();
    initButtons();
}

void loop(){
    tempSensors.requestTemperatures();
    float tempIn = tempSensors.getTempCByIndex(1);
    float tempOut = tempSensors.getTempCByIndex(0);

    minTemperature = min(minTemperature, tempOut);
    maxTemperature = max(maxTemperature, tempOut);

    actionBasedOnTemperature(tempOut);

    if(digitalRead(GREEN_BUTTON) == LOW){
        printMIN(minTemperature);
    }else if(digitalRead(RED_BUTTON) == LOW){
        printMAX(maxTemperature);
    }else if(tempOut < 27) {
        printLCD(tempIn, tempOut);
    }

   
}