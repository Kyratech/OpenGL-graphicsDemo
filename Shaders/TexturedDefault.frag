#version 400 core
in vec2 texCoordFrag;

out vec4 colour;

uniform vec4 baseColour;
uniform sampler2D ourTexture;

void main()
{
    colour = baseColour * texture2D(ourTexture, texCoordFrag);
}
