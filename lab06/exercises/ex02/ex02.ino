#include "LedRGB.h"
#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

LiquidCrystal_I2C lcd(0x27, 16, 2);

LedRGB RGB;

void setup(){
    lcd.init();
    lcd.noBacklight();
    lcd.clear();

    RGB.init(LED_RED, LED_GREEN, LED_BLUE);
    RGB.setColorByName("MAGENTA");
}

void loop(){

}