#include "precomp.h"
#include "shape.h"

bool Shape::Draw()
{
  glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
  glVertexAttribPointer(
                        0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*)0
                        );

  glDrawArrays(GL_TRIANGLES, 0, _numVertices);

  return true;
}

Shape::~Shape()
{
  if (_buffer)
  {
    delete _buffer;
  }
}

