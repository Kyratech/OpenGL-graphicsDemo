#ifndef MESH_H
#define MESH_H

#include <iostream>

#include "Introduction.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Mesh
{
public:
    /* Constructor */
    Mesh(const std::vector<Vertex> vertices, const GLchar* texturePath, GLfloat colour[3])
    {
        vertexCount = vertices.size();
        r = colour[0];
        g = colour[1];
        b = colour[2];

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);

        //Set up the vertex buffers
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(struct Vertex), &vertices[0], GL_STATIC_DRAW);

        //Set the vertex attrib pointers
        //Vertex positions
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(struct Vertex), (const GLvoid*) offsetof (struct Vertex, position));
        glEnableVertexAttribArray(0);
        //Vertex texture coordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*) offsetof (struct Vertex, textureCoords));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        //Generate the texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        //Set the wrapping style to repeat (This is on by default, but the code is here for completeness)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //Repeat on X
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //Repeat on Y

        //Set the texture filtering to nearest (again, only for completeness as it is the default)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        //Load in the texture
        int width, height, n;
        unsigned char* image = stbi_load(texturePath, &width, &height, &n, 3);
        if(image != NULL)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::cout << "Loaded texture at: " << texturePath << std::endl;
            std::cout << "Image stats: " << width << ", " << height << ", " << n << std::endl;
            std::cout << "First four bytes: " << (int)image[0] << ", " << (int)image[1] << ", " << (int)image[2] << ", " << (int)image[3] << std::endl;
        }
        else
        {
            std::cout << "Failed to load texture at: " << texturePath << std::endl;
        }
        //Clean-up
        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /* Draw the mesh with the supplied texture */
    void Draw(Shader shader)
    {
        GLint colourLocation = glGetUniformLocation(shader.getShaderProgram(), "baseColour");
        glUniform4f(colourLocation, r, g, b, 1.0f);

        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.getShaderProgram(), "ourTexture"), 0);

		glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }

private:
    GLuint VAO, VBO, texture;
    int vertexCount;
    uint8_t r,g,b;
};

#endif // MESH_H
