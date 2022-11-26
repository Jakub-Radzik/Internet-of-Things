#include <LedRGB.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3


LedRGB RGB;

void setup(){
    RGB.init(LED_RED, LED_GREEN, LED_BLUE);
    RGB.setColorByName("MAGENTA");
}

void loop(){

}