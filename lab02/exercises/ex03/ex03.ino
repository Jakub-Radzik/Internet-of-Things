#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int CURRENT_COLOR;
int PREVIOUS_COLOR;
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

    PREVIOUS_COLOR = LED_BLUE;
    CURRENT_COLOR = LED_RED;
}

void changeLedBrightness(){
    LED_BRIGHTNESS = (LED_BRIGHTNESS + 2) % (LED_MAX - LED_MIN + 1) + LED_MIN;
}

void changeLedColor(){

    PREVIOUS_COLOR = CURRENT_COLOR;

    if(CURRENT_COLOR == LED_GREEN){
        CURRENT_COLOR = LED_BLUE;
    }
    
    else if(CURRENT_COLOR == LED_RED){
        CURRENT_COLOR = LED_GREEN;
    }

    else if(CURRENT_COLOR == LED_BLUE){
        CURRENT_COLOR = LED_RED;
    }
    
}

void setup()
{
    initRGB();
}

void loop()
{  
    analogWrite(PREVIOUS_COLOR, LED_MAX - LED_BRIGHTNESS);
    analogWrite(CURRENT_COLOR, LED_BRIGHTNESS);

    changeLedBrightness();

    if (LED_BRIGHTNESS == 0)
        changeLedColor();

    delay(10);
}
