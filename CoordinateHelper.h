#ifndef COORDINATE_HELPER_H
#define COORDINATE_HELPER_H

class CoordinateHelper
{
 public:
 
  static void SetGameDimensions(GLfloat width, GLfloat height) {
    _gameWidth = width; _gameHeight = height;
    std::cout << "Dimensions = (" << width << ", " << height << ")" << std::endl; 
  }

  static GLfloat getGameHeight() {
    return _gameHeight;
  }

  static GLfloat getGameWidth() {
    return _gameWidth;
  }

  static GLfloat TranslateXToOpenGL(GLfloat x, bool scaleOnly = false) {
    // std::cout << "Params X = (" << x << ", " << _gameWidth << ")" << std::endl;
    if (x >= 0 &&
        x < _gameWidth&&
        _gameWidth > 0)
    {
      GLfloat scaleValue = (x / (GLfloat)_gameWidth) * 2.0f;

      if (!scaleOnly) {
        return scaleValue - 1.0f;
      }
      else {
        return scaleValue;
      }
    }
    else if (x >= _gameWidth) {
      return 1.0f; // Clip to max value
    }
    else if (x < 0) {
      return -1.0f;
    }
    else {
      return 0.0f;
    }
  }

  static GLfloat TranslateYToOpenGL(GLfloat y, bool scaleOnly = false) {
    // std::cout << "Params Y = (" << y << ", " << _gameHeight << ")" << std::endl;

    if (y < _gameHeight && _gameHeight > 0) {
      GLfloat scaleValue = (y / (GLfloat)_gameHeight) * 2.0f;

      if (!scaleOnly) {
        return 1 - scaleValue;
      }
      else {
        return scaleValue;
      }
    }
    else if (y >= _gameHeight) {
      return 1.0f; // Clip to max value
    }
    else if (y < 0) {
      return -1.0f;
    }
    else {
      return 0.0f;
    }
  }
  

 private:
  static GLfloat _gameWidth, _gameHeight;
};

#endif
