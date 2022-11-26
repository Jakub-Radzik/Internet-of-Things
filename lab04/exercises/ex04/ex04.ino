#include <LiquidCrystal_I2C.h>
#define POTENTIOMETER A0
LiquidCrystal_I2C lcd(0x27, 16, 2);
int prevValue;

void setup()
{
    prevValue = -1;
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    while (!Serial)
    { /* just wait */
    }
}

void loop()
{
    int value = analogRead(POTENTIOMETER);
    if(value != prevValue){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(value);
    }
    Serial.println(value);
}