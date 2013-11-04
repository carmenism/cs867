#ifndef PICKCOLOR_H
#define PICKCOLOR_H

class PickColor {
public:
    PickColor();
    PickColor(const PickColor& c);
    PickColor(unsigned char red, unsigned char green, unsigned char blue);

    unsigned char r, g, b;
};

#endif /* PICKCOLOR_H */