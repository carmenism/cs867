/**
 * Color.cpp - A class abstraction for gl color specification. This only uses
 *  the float version, but it could be extended if it ever proved useful to be
 *  more generic.  It supports rgb and rgba.
 *
 * @author Carmen St. Jean (crr8, carmen@cs.unh.edu)
 *         Based on Color.cpp by Dan Bergeron.
 *
 * UNH CS 870, fall 2012
 *
 * History:
 *  10/07/2012: Modified slightly to incorporate into homework assignment.
 *  09/24/2012: For now this is little more than a struct.
 */
#include "Color.h"

//------------- simple constructors -----------------------
Color::Color() {
    r = g = b = 0.0f;
}

Color::Color( float red, float green, float blue ) {
    // Should check that values are in the range [0,1]
    r = red;
    g = green;
    b = blue;
}

Color::Color( const Color& col ) {
    r = col.r;
    g = col.g;
    b = col.b;
}

void Color::getColorFromVelocity(float velocity, float &r, float &g, float &b) {
    Color *c = getColorFromHue(velocity);
    r = c->r;
    g = c->g;
    b = c->b;

    delete c;
}

// http://stackoverflow.com/questions/180/function-for-creating-color-wheels
Color *Color::getColorFromHue(float hue) {
    float saturation = 1.0;
    float brightness = 0.5;

    return hslToRgb(hue, saturation, brightness);
}

// http://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
Color *Color::hslToRgb(float h, float s, float l) {
    if (s == 0) {
        return new Color(l, l, l);
    }

    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2.0f * l - q;

    float r = hueToRgb(p, q, h + 1.0f / 3.0f);
    float g = hueToRgb(p, q, h);
    float b = hueToRgb(p, q, h - 1.0f / 3.0f);

    return new Color(r, g, b);
}

float Color::hueToRgb(float p, float q, float t) {
    if (t < 0) {
        t = t + 1;
    }

    if (t > 1) {
        t = t - 1;
    }

    if (t < (1.0 / 6.0)) {
        return p + (q - p) * 6 * t;
    }

    if (t < (1.0 / 2.0)) {
        return q;
    }

    if (t < (2.0 / 3.0)) {
        return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    }

    return p;
}