#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
 public:
  virtual bool Initialize() = 0;
  virtual bool Draw();
  virtual bool Update() = 0;
  ~Shape();
 protected:
  GLuint _vertexBuffer;
  GLint _bufferSize;
  GLfloat *_buffer;
  GLint _numVertices;
};
#endif
