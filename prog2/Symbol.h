#ifndef SYMBOL_H_
#define SYMBOL_H_

class Color;

class Symbol {
public:
   Symbol();
   virtual ~Symbol();
   
   /*void setLocation(float x, float y) { setX(x); setY(y); }
   void setX(float x) { this->x = x; }
   void setY(float y) { this->y = y; }
   float getX() { return x; }
   float getY() { return y; }*/

   float getRotation() { return rotation; }
   void setRotation(float r) { rotation = r; }

   float getWidth() { return width; }
   float getHeight() { return height; }
   void setSize(float w, float h) { width = w; height = h; }

   Color *getFillColor() { return fillColor; }
   void setFillColor(float r, float g, float b); // set color
   void setFillColor(Color *c) { fillColor = c; }
   
   float getBorderWidth() { return borderWidth; }
   void setBorderWidth(float w) { borderWidth = w; }

   Color *getBorderColor() { return borderColor; }
   void setBorderColor(float r, float g, float b); // set boundary color
   void setBorderColor(Color *c) { borderColor = c; }

   bool getDrawFill() { return drawFill; }
   void setDrawFill(bool df) { drawFill = df; }

   bool getDrawBorder() { return drawBorder; }
   void setDrawBorder(bool db) { drawBorder = db; }

   void draw();//float x, float y);   
   
   virtual void drawFillAtOrigin() = 0; // to be overwritten   
   virtual void drawOutlineAtOrigin() = 0; // to be overwritten
protected: 
   //float x, y;
   float width, height;          // size of the object
   float rotation;               // rotation
   float borderWidth;            // width of the boundary

   Color *fillColor;             // color
   Color *borderColor;           // boundary color

   bool drawFill;               // true to draw fill color
   bool drawBorder;             // true to draw boundary
};

#endif /*SYMBOL_H_*/