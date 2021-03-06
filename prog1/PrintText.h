#ifndef PRINTTEXT_H_
#define PRINTTEXT_H_

#include <string>
#include <glut.h>
#include <sstream>

#define DEFAULT_FONT GLUT_BITMAP_HELVETICA_18

enum {HORIZ_LEFT, HORIZ_RIGHT, HORIZ_CENTER};
enum {VERT_BOTTOM, VERT_TOP, VERT_CENTER};

class PrintText
{
public:
    static void drawStrokeText(std::string text, float x, float y, float h, int horizAlign = HORIZ_LEFT, int vertAlign = VERT_BOTTOM, bool whiteBg = false, float rotate = 0);
    static void drawWhiteBackground(std::string label, float fontHeight, float padding);
    static float strokeWidth(std::string text, float h);
};

inline std::string toStr(float x) {
  std::ostringstream o;

  if (!(o << x)) {
      return NULL;
      //throw BadConversion("stringify(double)");
  }

  return o.str();
}

inline std::string numToStr(float value) {
    int intValue = (int) value;

    if (intValue != 0 && intValue == value) {
        if (intValue % 1000000 == 0) {
            float newValue = value / 1000000;

            return toStr(newValue) + "M";
        } else if (intValue % 1000 == 0) {
            float newValue = value / 1000;

            return toStr(newValue) + "k";
        }
    }

    return toStr(value);
}   


#endif /* PRINTTEXT_H_ */