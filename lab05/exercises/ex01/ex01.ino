#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED_RED 6
#define LED_BLUE 3

#define ENCODER1 A2
#define ENCODER2 A3

void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);

    lcd.init();
    lcd.noBacklight();

    Serial.begin(9600);
    while (!Serial)
    { /* just wait */
    }
}

void loop()
{
    int enc1 = digitalRead(ENCODER1);
    int enc2 = digitalRead(ENCODER2);

    digitalWrite(LED_RED, enc1);
    digitalWrite(LED_BLUE, enc2);
    Serial.println(String(enc1) + " " + String(enc2));
}
