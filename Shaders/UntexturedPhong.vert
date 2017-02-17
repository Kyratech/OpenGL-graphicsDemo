#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 MVPmatrix;
uniform mat4 modelMatrix;

out vec3 fragPos;
out vec3 normalVec;

void main()
{
    gl_Position = MVPmatrix * vec4(position, 1.0f);
    fragPos = vec3(modelMatrix * vec4(position, 1.0f));
    normalVec = normal;
}

