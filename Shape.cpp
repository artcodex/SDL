#include "precomp.h"
#include "CoordinateHelper.h"
#include "shape.h"

bool Shape::Draw()
{
  GLuint shaderID = CoordinateHelper::getShaderMatrix();
  glm::mat4 proj, view;

  CoordinateHelper::getProjectionMatrix(proj);
  CoordinateHelper::getCameraMatrix(view);

  glm::mat4 mvp = proj * view * _model;

  //std::cout << "mvp =" << shaderID << std::endl;;

  glUniformMatrix4fv(shaderID, 1, GL_FALSE, &mvp[0][0]);
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

