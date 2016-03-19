#include "precomp.h"
#include "CoordinateHelper.h"
#include "Rectangle.h"


Rectangle::Rectangle(GLint left, GLint top, GLint width, GLint height)
{
  _left = left;
  _top = top;
  _width = width;
  _height = height;
}


bool Rectangle::Initialize()
{
  _numVertices = RECTANGLE_VERTICES_COUNT;
  _bufferSize = _numVertices * 3;
  std::cout << _bufferSize << std::endl;

  GLfloat fLeft   = CoordinateHelper::TranslateXToOpenGL(_left);
  GLfloat fWidth  = CoordinateHelper::TranslateXToOpenGL(_width, true);
  GLfloat fTop    = CoordinateHelper::TranslateYToOpenGL(_top);
  GLfloat fHeight = CoordinateHelper::TranslateYToOpenGL(_height, true);

  std::cout << "Params = (" << fTop << ", " << fLeft << ", " << fWidth << ", " << fHeight << ")" << std::endl;

  _buffer = new GLfloat[_bufferSize] {
    fLeft, fTop, 0.0f,
    fLeft, fTop - fHeight, 0.0f,
    fLeft + fWidth, fTop - fHeight, 0.0f,
    fLeft + fWidth, fTop - fHeight, 0.0f,
    fLeft + fWidth, fTop, 0.0f,
    fLeft, fTop, 0.0f
  };

  for (int i=0; i < _bufferSize; i++)
    {
      std::cout << _buffer[i] << " ";

      if (((i + 1) % 3) == 0) {
        std::cout << std::endl;
      }
    }

  std::cout << std::endl;

 	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _bufferSize * sizeof(GLfloat), _buffer, GL_STATIC_DRAW);
  return true;
}
