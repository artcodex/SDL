#include "precomp.h"
#include "TexturedRectangle.h"

TexturedRectangle::TexturedRectangle(
       GLfloat left,
       GLfloat top,
       GLfloat width,
       GLfloat height,
       float32 density,
       std::string& filename,
       GLuint programTexID) : Rectangle(left, top, width, height, density) {
  _filename = filename;
  _progTexID = programTexID;
}

TexturedRectangle::~TexturedRectangle() {
  if (_uvBuffer) {
    delete _uvBuffer;
    _uvBuffer = nullptr;
  }
}

bool TexturedRectangle::Draw() {
  //Binding the texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _textureID);
  glUniform1i(_progTexID, 0);

  glBindBuffer(GL_ARRAY_BUFFER, _uvBufferID);
  glVertexAttribPointer(
                        1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*)0
                        );

  
  return Rectangle::Draw();
}

bool TexturedRectangle::Initialize() {
  // Call base class
  if (Rectangle::Initialize()) {
    _surface = SDL_LoadBMP(_filename.c_str());
 
    if (_surface) {
      std::cout << "Setting up texture: " << _filename << std::endl;

      std::cout << "Setting up the uv matrix ..." << std::endl;
      _uvBuffer = new GLfloat[_numVertices*2] {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
      };

      std::cout << "UV coord space: " << std::endl;
      for (int i=0; i < _numVertices*2; i++)
        {
          std::cout << _uvBuffer[i] << " ";

          if (((i + 1) % 2) == 0) {
            std::cout << std::endl;
          }
        }

      std::cout << std::endl;

      glGenBuffers(1, &_uvBufferID);
      glBindBuffer(GL_ARRAY_BUFFER, _uvBufferID);
      glBufferData(GL_ARRAY_BUFFER, (_numVertices * 2) * sizeof(GLfloat), _uvBuffer, GL_STATIC_DRAW);

      glGenTextures(1, &_textureID);
      glBindTexture(GL_TEXTURE_2D, _textureID);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _surface->w, _surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, _surface->pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glGenerateMipmap(GL_TEXTURE_2D);
    }

    return true;
  }
  else {
    return false;
  }
}




