#ifndef PRECOMP_H
#define PRECOMP_H

#define WINDOWS

#ifdef WINDOWS
#include <SOIL2.h>
#include <GL/glew.h>
#include <glfw\glfw3.h>
#else
#include <SDL.h>
#include <OpenGL/gl3.h>
#endif

#include <Box2D/Box2D.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "physics.h"

#endif
