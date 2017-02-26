#ifndef INTRO_H
#define INTRO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderLoader.h"
#include "BLCamera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

//static const AMBIENT_STRENGTH = 0.1f;
static const glm::vec3 LIGHT_COLOUR = glm::vec3(0.8f, 0.8f, 0.8f);
static const glm::vec3 LIGHT_POS = {-6.64463f, 7.07107f, -2.41845f};

struct Vertex
{
    GLdouble position[3];
    GLdouble normal[3];
    GLfloat textureCoords[2];
};

/* Set up the camera */
glm::vec3 cameraPos = glm::vec3(0.0f, 10.0f, 0.0f);

ThreeD_Camera camera(cameraPos);

#endif // INTRO_H
