#ifndef TEXTURED_RECTANGLE_H
#define TEXTURED_RECTANGLE_H

#include "Rectangle.h"

class TexturedRectangle : public Rectangle {
 public:
  TexturedRectangle(GLfloat left, GLfloat top, GLfloat width, GLfloat height, float32 density, std::string& filename, GLuint programTexID);
  ~TexturedRectangle();
  virtual bool Initialize();
  virtual bool Draw();
 protected:
  GLuint _textureID;
  GLuint _uvBufferID;
  GLuint _progTexID;
  GLfloat *_uvBuffer;
  SDL_Surface* _surface;
  std::string _filename;
};

#endif
