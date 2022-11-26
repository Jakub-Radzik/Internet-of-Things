#include <LiquidCrystal_I2C.h>
#define RED_BUTTON 2
#define GREEN_BUTTON 4
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup()
{
    lcd.init();
    lcd.noBacklight();
    initButtons();
    Serial.begin(9600);
    while (!Serial)
    { /* just wait */
    }
}

void loop()
{
    String str = String(digitalRead(GREEN_BUTTON)) + " " + String(digitalRead(RED_BUTTON));
    Serial.println(str);
}