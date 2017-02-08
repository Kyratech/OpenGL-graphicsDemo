#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 MVPmatrix;

out vec2 texCoordFrag;

void main()
{
    gl_Position = MVPmatrix * vec4(position, 1.0f);
    texCoordFrag = texCoord;
}
