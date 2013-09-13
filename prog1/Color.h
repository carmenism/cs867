/**
 * Color.h - A class abstraction for gl color specification. This only uses the
 *  float version, but it could be extended if it ever proved useful to be more
 *  generic.  It supports rgb and rgba.
 *
 * @author Carmen St. Jean (crr8)
 *         Based on Color.h by Dan Bergeron.
 *
 * UNH CS 867, fall 2013
 */
#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color();
    Color( const Color& c );
    Color( float red, float green, float blue, float alpha = 1.0 );

    float r, g, b, a;
};

#endif /* COLOR_H */