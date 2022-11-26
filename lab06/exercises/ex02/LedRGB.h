#ifndef LEDRGB_H_
#define LEDRGB_H_

#include "Arduino.h"

class LedRGB
{
public:
    void init(byte red, byte green, byte blue);
    void setColor(bool red, bool green, bool blue);
    void setColorByName(String color);

private:
    byte red_;
    byte green_;
    byte blue_;
};

#endif