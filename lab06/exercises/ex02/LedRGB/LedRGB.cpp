#include "LedRGB.h"

void LedRGB::init(byte red, byte green, byte blue){
    red_ = red;
    pinMode(red, OUTPUT);
    digitalWrite(red, LOW);

    green_ = green;
    pinMode(green, OUTPUT);
    digitalWrite(green, LOW);

    blue_ = blue;
    pinMode(blue, OUTPUT);
    digitalWrite(blue, LOW);
}

void LedRGB::setColor(bool red, bool green, bool blue){
    digitalWrite(red_, red ? HIGH : LOW);
    digitalWrite(green_, green ? HIGH : LOW);
    digitalWrite(blue_, blue ? HIGH : LOW);
}


void LedRGB::setColorByName(String color){
    if (color == "RED"){
        setColor(true, false, false);
    }else if (color == "GREEN"){
        setColor(false, true, false);
    }else if (color == "BLUE"){
        setColor(false, false, true);
    }else if (color == "YELLOW"){
        setColor(true, true, false);
    }else if (color == "CYAN"){
        setColor(false, true, true);
    }else if (color == "MAGENTA"){
        setColor(true, false, true);
    }else if (color == "WHITE"){
        setColor(true, true, true);
    }
}