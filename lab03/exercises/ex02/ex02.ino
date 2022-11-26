#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3
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

void setup()
{
    initRGB();
}

void blinkGreenLed()
{
    const unsigned long Delay = 1000UL;
    static int ledState = LOW;
    static unsigned long lastBlinkChange = 0UL;

    if (millis() - lastBlinkChange >= Delay)
    {
        ledState = ledState == HIGH ? LOW : HIGH;
        digitalWrite(LED_GREEN, ledState);
        lastBlinkChange += Delay;
    }
}

void blinkRedLed()
{
    const unsigned long Delay = 900UL;
    static int ledState = LOW;
    static unsigned long lastBlinkChange = 0UL;

    if (millis() - lastBlinkChange >= Delay)
    {
        ledState = ledState == HIGH ? LOW : HIGH;
        digitalWrite(LED_RED, ledState);
        lastBlinkChange += Delay;
    }
}

void blinkBlueLed()
{
    const unsigned long Delay = 1100UL;
    static int ledState = LOW;
    static unsigned long lastBlinkChange = 0UL;

    if (millis() - lastBlinkChange >= Delay)
    {
        ledState = ledState == HIGH ? LOW : HIGH;
        digitalWrite(LED_BLUE, ledState);
        lastBlinkChange += Delay;
    }
}


void loop()
{
    blinkGreenLed();
    blinkRedLed();
    blinkBlueLed();
}
