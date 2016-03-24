#include "precomp.h"
#include "CoordinateHelper.h"

GLfloat CoordinateHelper::_gameHeight = 0;
GLfloat CoordinateHelper::_gameWidth = 0;
GLuint CoordinateHelper::_matrixParam = 0;
glm::mat4 CoordinateHelper::_projection;
glm::mat4 CoordinateHelper::_camera;
