#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCE_PERIOD 10UL

//#include<LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 7, 10, 9, 8);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool running;
int counter;

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
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

void printCounter(int time)
{
  String seconds = time % 60 < 10 ? '0' + String(time % 60) : String(time % 60);
  String minutes = String(counter / 60);
    
  lcd.setCursor(0, 0);
  lcd.print(minutes + ':' + seconds);
}

void incrementCounter()
{
    const unsigned long Delay = 1000UL;
    static unsigned long lastIncrementChange = 1000UL;

    if (millis() - lastIncrementChange >= Delay)
    {
        counter += 1;
        printCounter(counter);
        lastIncrementChange = millis();
    }
}

void initCounter()
{
    running = true;
    counter = 0;
}

void toggleCounter()
{
    running = !running;
}

void resetCounter()
{
    counter = 0;
    running = false;
    lcd.clear();
    printCounter(counter);
}

void setup()
{
    initButtons();
    initCounter();
    lcd.init();
    lcd.backlight();
}


void loop()
{
    if (isGreenButtonPressed())
    {
        toggleCounter();
    }

    if(isRedButtonPressed())
    {
        resetCounter();
    }

    if(running)
    {
        incrementCounter();
    }
}
