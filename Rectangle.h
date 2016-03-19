#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

#define RECTANGLE_VERTICES_COUNT 6

class Rectangle : public Shape
{
 public:
  Rectangle(GLint left, GLint top, GLint width, GLint height);
  virtual bool Initialize() override;
 protected:
  GLint _top;
  GLint _left;
  GLint _width;
  GLint _height;
};

#endif
