#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

int convertBrightness(String brightness) {
    brightness.trim();
    brightness.toLowerCase();
    if(brightness == ""){
        return 100;
    }

    int converted = brightness.toInt();

    if(converted < 0){
        return 0;
    }

    if(converted > 100){
        return 100;
    }

    return converted;
} 

void monitorFeedback(String color, int brightness){
    Serial.println(color + " at " + brightness);
}

void changeColor(String color, int brightness) {
        if (color == "blue")
        {
            analogWrite(LED_BLUE, brightness);
            monitorFeedback(color, brightness);
        }
        else if (color == "red")
        {
            analogWrite(LED_RED, brightness);
            monitorFeedback(color, brightness);
        }
    	else if (color == "green")
        {
            analogWrite(LED_GREEN, brightness);
            monitorFeedback(color, brightness);
        }
        else if (color == "builtin")
        {
            digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) == HIGH ? LOW : HIGH);
            monitorFeedback(color, digitalRead(LED_BUILTIN) == HIGH ? LOW : HIGH * 100);
        }
        else
        {
            Serial.println(String("Unknown color '") + color + "'");
        }
}

void setup()
{
    initRGB();
    lcd.init();
    Serial.begin(9600);
    while (!Serial)
    { /* just wait */
    }
}

void loop()
{
   if (Serial.available() > 0)
    {
        String color = Serial.readStringUntil(':');
        color.trim();
        color.toLowerCase();
     
        int brightness = convertBrightness(Serial.readStringUntil('\n'));
        changeColor(color, brightness);
        
    }
}
