#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define ENCODER1 A2
#define ENCODER2 A3

#define DEBOUNCE_PERIOD 20UL

String MENU[3] = {"Red", "Green", "Blue"};
int MENU_LENGTH;
int menuIndex;
bool isSubMenu = false;
int LEDS[3] = {0, 0, 0};
int minLED = 0;
int maxLED = 255;

int prevEn1 = LOW;
unsigned long lastChangeTimestamp = 0UL;

void initEncoder(){
    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);
}

void initButtons(){
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void initLed(){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void initLcd(){
    lcd.init();
    lcd.begin(16, 2);
    lcd.backlight();
}

void initMenu(){
    menuIndex = 0;
    MENU_LENGTH = sizeof(MENU) / sizeof(MENU[0]);
    if(MENU_LENGTH >= 2){
        printMenu(MENU[0], MENU[1]);
    }else if(MENU_LENGTH == 1){
        printMenu(MENU[0], " ");
    }
}

void printMenu(String top, String bottom){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("> " + top);
    lcd.setCursor(0, 1);
    lcd.print(bottom);
}

void printBrightnessMenu(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(MENU[menuIndex] + ": " + LEDS[menuIndex]);
}

void scrollMenu(int by){
    if(by < 0){
        if(menuIndex + by < 0){
            menuIndex = 0;
        }else {
            menuIndex = menuIndex + by;
        }
    }

    if(by > 0){
        if(menuIndex + by > MENU_LENGTH - 1){
            menuIndex = MENU_LENGTH - 1;
        }else {
            menuIndex = menuIndex + by;
        }
    }
}

void updateLED(int option, int brightness){
    if(option == 0){
        analogWrite(LED_RED, brightness);
    }else if (option == 1){
        analogWrite(LED_GREEN, brightness);
    }else if(option == 2){
        analogWrite(LED_BLUE, brightness);
    }
}

bool isGreenButtonPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
}

bool isRedButtonPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
}

void setup()
{
   initEncoder();
   initButtons();
   initLcd();
   initLed();
   initMenu();
}

void loop(){
    int en1 = digitalRead(ENCODER1);
    int en2 = digitalRead(ENCODER2);
    bool redPressed = isRedButtonPressed();
    bool greenPressed = isGreenButtonPressed();

    unsigned long timestamp = millis();
    bool encoderMoved = en1 == LOW && prevEn1 == HIGH && timestamp > lastChangeTimestamp + DEBOUNCE_PERIOD;
    if (encoderMoved){
        if (en2 == HIGH){
            if(isSubMenu){
                if (LEDS[menuIndex] < maxLED){
                    LEDS[menuIndex] = LEDS[menuIndex] + 15 > maxLED ? maxLED : LEDS[menuIndex] + 15;
                }
            }else {
                scrollMenu(1);
            }
            
        }
        else{
            if(isSubMenu){
                if (LEDS[menuIndex] > minLED){
                    LEDS[menuIndex] = LEDS[menuIndex] - 15 < minLED ? minLED : LEDS[menuIndex] - 15;
                }
            }else {
                scrollMenu(-1);
            }
        }
        lastChangeTimestamp = timestamp;

        if(isSubMenu){
            printBrightnessMenu();
        }else {
            if(MENU_LENGTH == 1 || menuIndex == MENU_LENGTH - 1) {
                printMenu(MENU[menuIndex], "");
            }else if(MENU_LENGTH >= 2){
                printMenu(MENU[menuIndex], MENU[menuIndex + 1]);
            }
        }
        
    }

    if(greenPressed){
       isSubMenu = true;
    }

    if(redPressed){
       isSubMenu = false;
    }

    if(encoderMoved && isSubMenu){
        updateLED(menuIndex, LEDS[menuIndex]);
    }

    if(redPressed || greenPressed || encoderMoved){
        if(isSubMenu){
            printBrightnessMenu();
        }else {
            if(MENU_LENGTH == 1 || menuIndex == MENU_LENGTH - 1) {
                printMenu(MENU[menuIndex], "");
            }else if(MENU_LENGTH >= 2){
                printMenu(MENU[menuIndex], MENU[menuIndex + 1]);
            }
        }
    }

    

    prevEn1 = en1;
}
