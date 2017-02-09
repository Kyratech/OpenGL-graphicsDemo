#ifndef UV_SPHERE_H
#define UV_SPHERE_H

#include "Introduction.h"
#include <math.h>
#include <iostream>

/*  Produce the vertex data for a sphere with smooth shading.
    The normal at each vertex is along the direction from the centre to the vertex.
    Segments = number of bands of quads split by lines of longitude
    Rings = number of bands of quads split by the lines of latitude
    There are (rings + 1) lines of latitude, inc the points at the top and bottom
    No generated UVs. Sorry.
*/
const std::vector<struct Vertex> GetSpherePhong(int segments, int rings, double radius)
{
    std::vector<struct Vertex> vertices;

    double ringAngle = 180.0f / segments;
    double segmentAngle = 360.0f / rings;

    /*
     * NB: rn is the nth line of latitude, starting at the top
     * bn is the nth line of longitude, starting from positive X direction
     * This notation is to save space; the parameters still define the number of
     * quad bands in the respective direction, NOT the lines of lat/long
     */

    //Oth line of latitude is the point on top
    int i;
    double theta = glm::radians(90.0 - ringAngle);
    for(i = 0; i < segments; i++)
    {
        struct Vertex r0 = {{0.0, radius, 0.0},   {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}};

        double phii = glm::radians(i * segmentAngle); //phi(i)
        double r1biX = radius * cos(theta) * cos(phii);
        double r1biY = radius * sin(theta);
        double r1biZ = radius * cos(theta) * sin(phii);
        glm::vec3 normali = glm::normalize(glm::vec3(r1biX, r1biY, r1biZ));
        struct Vertex r1bi = {{r1biX, r1biY, r1biZ},    {normali.x, normali.y, normali.z},    {0.0f, 0.0f}};

        double phii2 = glm::radians(((i + 1) % segments) * segmentAngle); //phi(i+1)
        double r1bi2X = radius * cos(theta) * cos(phii2);
        double r1bi2Y = radius * sin(theta);
        double r1bi2Z = radius * cos(theta) * sin(phii2);
        glm::vec3 normali2 = glm::normalize(glm::vec3(r1bi2X, r1bi2Y, r1bi2Z));
        struct Vertex r1bi2 = {{r1bi2X, r1bi2Y, r1bi2Z},    {normali2.x, normali2.y, normali2.z},    {0.0f, 0.0f}};

        vertices.push_back(r0);
        vertices.push_back(r1bi);
        vertices.push_back(r1bi2);

        //std::cout << "RingAngle: " << ringAngle << ", SegmentAngle: " << segmentAngle << std::endl;
        //std::cout << "r1bi:(" << r1biX << ","  << r1biY << "," << r1biZ << ")" << std::endl;
    }

    //Middle rings are made from quads (kinda...), so require different attention
    for(int j = 1; j < rings - 1; j++)
    {
        double thetaj = glm::radians(90 - (j * ringAngle)); //theta(j)
        double thetaj2 = glm::radians(90 - ((j + 1) * ringAngle)); //theta(j+1)
        for(i = 0; i < segments; i++)
        {
            double phii = glm::radians(i * segmentAngle); //phi(i)
            double phii2 = glm::radians(((i + 1) % segments) * segmentAngle); //phi(i+1)

            double rjbiX = radius * cos(thetaj) * cos(phii);
            double rjbiY = radius * sin(thetaj);
            double rjbiZ = radius * cos(thetaj) * sin(phii);
            glm::vec3 normalrjbi = glm::normalize(glm::vec3(rjbiX, rjbiY, rjbiZ));
            struct Vertex rjbi = {{rjbiX, rjbiY, rjbiZ},    {normalrjbi.x, normalrjbi.y, normalrjbi.z}, {0.0f, 0.0f}};;

            double rjbi2X = radius * cos(thetaj) * cos(phii2);
            double rjbi2Y = radius * sin(thetaj);
            double rjbi2Z = radius * cos(thetaj) * sin(phii2);
            glm::vec3 normalrjbi2 = glm::normalize(glm::vec3(rjbi2X, rjbi2Y, rjbi2Z));
            struct Vertex rjbi2 = {{rjbi2X, rjbi2Y, rjbi2Z},    {normalrjbi2.x, normalrjbi2.y, normalrjbi2.z}, {0.0f, 0.0f}};;

            double rj2biX = radius * cos(thetaj2) * cos(phii);
            double rj2biY = radius * sin(thetaj2);
            double rj2biZ = radius * cos(thetaj2) * sin(phii);
            glm::vec3 normalrj2bi = glm::normalize(glm::vec3(rj2biX, rj2biY, rj2biZ));
            struct Vertex rj2bi = {{rj2biX, rj2biY, rj2biZ},    {normalrj2bi.x, normalrj2bi.y, normalrj2bi.z}, {0.0f, 0.0f}};;

            double rj2bi2X = radius * cos(thetaj2) * cos(phii2);
            double rj2bi2Y = radius * sin(thetaj2);
            double rj2bi2Z = radius * cos(thetaj2) * sin(phii2);
            glm::vec3 normalrj2bi2 = glm::normalize(glm::vec3(rj2bi2X, rj2bi2Y, rj2bi2Z));
            struct Vertex rj2bi2 = {{rj2bi2X, rj2bi2Y, rj2bi2Z},    {normalrj2bi2.x, normalrj2bi2.y, normalrj2bi2.z}, {0.0f, 0.0f}};;

            vertices.push_back(rjbi);
            vertices.push_back(rjbi2);
            vertices.push_back(rj2bi);

            vertices.push_back(rjbi2);
            vertices.push_back(rj2bi2);
            vertices.push_back(rj2bi2);

            std::cout << "r" << j << "b" << i << ":(" << rjbiX << ","  << rjbiY << "," << rjbiZ << ")" << std::endl;
            //Oh god, this is more code than I had hoped
            //Yeah, but I am particularly verbose
        }
    }

    //(rings + 1)th line of latitude is the point on bottom
    theta = glm::radians(ringAngle - 90);
    for(i = 0; i < segments; i++)
    {
        struct Vertex rn2 = {{0.0, -radius, 0.0},   {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}};

        double phii = glm::radians(i * segmentAngle); //phi(i)
        double rnbiX = radius * cos(theta) * cos(phii);
        double rnbiY = radius * sin(theta);
        double rnbiZ = radius * cos(theta) * sin(phii);
        glm::vec3 normali = glm::normalize(glm::vec3(rnbiX, rnbiY, rnbiZ));
        struct Vertex rnbi = {{rnbiX, rnbiY, rnbiZ},    {normali.x, normali.y, normali.z},    {0.0f, 0.0f}};

        double phii2 = glm::radians(((i + 1) % segments) * segmentAngle); //phi(i+1)
        double rnbi2X = radius * cos(theta) * cos(phii2);
        double rnbi2Y = radius * sin(theta);
        double rnbi2Z = radius * cos(theta) * sin(phii2);
        glm::vec3 normali2 = glm::normalize(glm::vec3(rnbi2X, rnbi2Y, rnbi2Z));
        struct Vertex rnbi2 = {{rnbi2X, rnbi2Y, rnbi2Z},    {normali2.x, normali2.y, normali2.z},    {0.0f, 0.0f}};

        vertices.push_back(rn2);
        vertices.push_back(rnbi);
        vertices.push_back(rnbi2);
    }

    return vertices;
}

#endif // UV_SPHERE_H
