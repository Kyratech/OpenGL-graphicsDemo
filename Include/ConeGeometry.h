#ifndef CONE_H
#define CONE_H

#include "Introduction.h"
#include <math.h>
#include <iostream>

/* Produce vertex data for a cone with smooth shading on the curved face
*/
const std::vector<Vertex> GetConePhong(int segments, double height, double radius)
{
    /* Minimum of 3 segments and 3 rings */
    if(segments < 3) segments = 3;

    std::vector<struct Vertex> vertices;

    double segmentAngle = 360.0f / segments;

    int i;
    //Curved surface
    for(i = 0; i < segments; i++)
    {
        double theta = glm::radians(segmentAngle * i);
        double theta2 = glm::radians(((i + 1) % segments) * segmentAngle);

        double iX = radius * cos(theta);
        double iY = -height / 2;
        double iZ = radius * sin(theta);
        glm::vec3 iNormal = glm::vec3(0, radius, 0) + glm::vec3(iX * height, 0, iZ * height);
        iNormal = glm::normalize(iNormal);
        struct Vertex iVert = {{iX, iY, iZ}, {iNormal.x, iNormal.y, iNormal.z}, {0.0f, 0.0f}};

        struct Vertex top = {{0, height/2, 0}, {iNormal.x, iNormal.y, iNormal.z}, {0.0f, 0.0f}};

        double i2X = radius * cos(theta2);
        double i2Y = -height / 2;//Yes, redundant. Readability and future flexibility reasons
        double i2Z = radius * sin(theta2);
        glm::vec3 i2Normal = glm::vec3(0, radius, 0) + glm::vec3(i2X * height, 0, i2Z * height);
        i2Normal = glm::normalize(i2Normal);
        struct Vertex i2Vert = {{i2X, i2Y, i2Z}, {i2Normal.x, i2Normal.y, i2Normal.z}, {0.0f, 0.0f}};

        vertices.push_back(iVert);
        vertices.push_back(top);
        vertices.push_back(i2Vert);
    }
    //Base
    for(i = 0; i < segments; i++)
    {
        double theta = glm::radians(segmentAngle * i);
        double theta2 = glm::radians(((i + 1) % segments) * segmentAngle);

        double iX = radius * cos(theta);
        double iY = -height / 2;
        double iZ = radius * sin(theta);
        struct Vertex iVert = {{iX, iY, iZ}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}};

        struct Vertex bottom = {{0, -height/2, 0}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}};

        double i2X = radius * cos(theta2);
        double i2Y = -height / 2;//Yes, redundant. Readability and future flexibility reasons
        double i2Z = radius * sin(theta2);
        struct Vertex i2Vert = {{i2X, i2Y, i2Z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}};

        vertices.push_back(iVert);
        vertices.push_back(bottom);
        vertices.push_back(i2Vert);
    }

    return vertices;
}
#endif // CONE_H
