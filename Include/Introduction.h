#ifndef INTRO_H
#define INTRO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.h"

struct Vertex
{
    GLdouble position[3];
    GLdouble normal[3];
    GLfloat textureCoords[2];
};

#endif // INTRO_H
