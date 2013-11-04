#include "PickColor.h"

PickColor::PickColor() {
    r = g = b = '\0';
}

PickColor::PickColor(const PickColor& col) {
    r = col.r;
    g = col.g;
    b = col.b;
}

PickColor::PickColor(unsigned char red, unsigned char green, unsigned char blue) {
    r = red;
    g = green;
    b = blue;
}