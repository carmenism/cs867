/**
 * Color.cpp - A class abstraction for gl color specification. This only uses
 *  the float version, but it could be extended if it ever proved useful to be
 *  more generic.  It supports rgb and rgba.
 *
 * @author Carmen St. Jean (crr8)
 *         Based on Color.cpp by Dan Bergeron.
 *
 * UNH CS 867, fall 2013
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

Color::Color( float red, float green, float blue, float alpha ) {
    // Should check that values are in the range [0,1]
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

Color::Color( const Color& col ) {
    r = col.r;
    g = col.g;
    b = col.b;
    a = col.a;
}