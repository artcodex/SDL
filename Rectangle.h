#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

#define RECTANGLE_VERTICES_COUNT 6

class Rectangle : public Shape
{
 public:
  Rectangle(GLfloat left, GLfloat top, GLfloat width, GLfloat height, float32 density);
  virtual bool Initialize() override;
  virtual bool Update() override;
  ~Rectangle();
  void SetBounds(GLfloat left, GLfloat top, GLfloat width, GLfloat height);
  void AddForce(b2Vec2 force);
 protected:
  GLfloat _top;
  GLfloat _left;
  GLfloat _width;
  GLfloat _height;
  b2Body* _body;
  float32 _density;
  glm::mat4 _trans;
};

#endif
