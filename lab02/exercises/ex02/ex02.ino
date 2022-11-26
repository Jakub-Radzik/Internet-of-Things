#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int LED_BRIGHTNESS;
int LED_MIN;
int LED_MAX;

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

    LED_MIN = 0;
    LED_MAX = 255;
    LED_BRIGHTNESS = LED_MIN;
}

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup()
{
    initButtons();
    initRGB();
}

void loop()
{
    if (digitalRead(GREEN_BUTTON) == LOW)
        LED_BRIGHTNESS = LED_BRIGHTNESS < LED_MAX ? LED_BRIGHTNESS + 1 : LED_MAX;

    if (digitalRead(RED_BUTTON) == LOW)
        LED_BRIGHTNESS = LED_BRIGHTNESS > LED_MIN ? LED_BRIGHTNESS - 1 : LED_MIN;
   
    analogWrite(LED_RED, LED_BRIGHTNESS);

    delay(5);
}
