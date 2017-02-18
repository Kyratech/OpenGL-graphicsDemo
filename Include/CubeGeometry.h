#ifndef CUBE_H
#define CUBE_H

#include "Introduction.h"

const std::vector<struct Vertex> GetCubeGeometry(double sideLength)
{
    double halfSide = sideLength / 2;
    //Vertices forming a 2D square made up of two triangles
	const std::vector<struct Vertex> vertices =
	{
		{{-halfSide, -halfSide, -halfSide},     {0.0f, 0.0f, -1.0f},    {0.0f, 0.0f}},
		{{halfSide, -halfSide, -halfSide},      {0.0f, 0.0f, -1.0f},    {1.0f, 0.0f}},
		{{halfSide,  halfSide, -halfSide},      {0.0f, 0.0f, -1.0f},    {1.0f, 1.0f}},
		{{halfSide,  halfSide, -halfSide},      {0.0f, 0.0f, -1.0f},    {1.0f, 1.0f}},
		{{-halfSide,  halfSide, -halfSide},     {0.0f, 0.0f, -1.0f},    {0.0f, 1.0f}},
		{{-halfSide, -halfSide, -halfSide},     {0.0f, 0.0f, -1.0f},    {0.0f, 0.0f}}, //Front

		{{-halfSide, -halfSide,  halfSide},     {0.0f, 0.0f, 1.0f},     {0.0f, 0.0f}},
		{{halfSide, -halfSide,  halfSide},      {0.0f, 0.0f, 1.0f},     {1.0f, 0.0f}},
		{{halfSide,  halfSide,  halfSide},      {0.0f, 0.0f, 1.0f},     {1.0f, 1.0f}},
		{{halfSide,  halfSide,  halfSide},      {0.0f, 0.0f, 1.0f},     {1.0f, 1.0f}},
		{{-halfSide,  halfSide,  halfSide},     {0.0f, 0.0f, 1.0f},     {0.0f, 1.0f}},
		{{-halfSide, -halfSide,  halfSide},     {0.0f, 0.0f, 1.0f},     {0.0f, 0.0f}}, //Back

		{{-halfSide,  halfSide,  halfSide},     {-1.0f, 0.0f, 0.0f},    {1.0f, 0.0f}},
		{{-halfSide,  halfSide, -halfSide},     {-1.0f, 0.0f, 0.0f},    {1.0f, 1.0f}},
		{{-halfSide, -halfSide, -halfSide},     {-1.0f, 0.0f, 0.0f},    {0.0f, 1.0f}},
		{{-halfSide, -halfSide, -halfSide},     {-1.0f, 0.0f, 0.0f},    {0.0f, 1.0f}},
		{{-halfSide, -halfSide,  halfSide},     {-1.0f, 0.0f, 0.0f},    {0.0f, 0.0f}},
		{{-halfSide,  halfSide,  halfSide},     {-1.0f, 0.0f, 0.0f},    {1.0f, 0.0f}}, //Left

		{{halfSide,  halfSide,  halfSide},      {1.0f, 0.0f, 0.0f},     {1.0f, 0.0f}},
		{{halfSide,  halfSide, -halfSide},      {1.0f, 0.0f, 0.0f},     {1.0f, 1.0f}},
		{{halfSide, -halfSide, -halfSide},      {1.0f, 0.0f, 0.0f},     {0.0f, 1.0f}},
		{{halfSide, -halfSide, -halfSide},      {1.0f, 0.0f, 0.0f},     {0.0f, 1.0f}},
		{{halfSide, -halfSide,  halfSide},      {1.0f, 0.0f, 0.0f},     {0.0f, 0.0f}},
		{{halfSide,  halfSide,  halfSide},      {1.0f, 0.0f, 0.0f},     {1.0f, 0.0f}}, //Right

		{{-halfSide, -halfSide, -halfSide},     {0.0f -1.0f, 0.0f},     {0.0f, 1.0f}},
		{{halfSide, -halfSide, -halfSide},      {0.0f -1.0f, 0.0f},     {1.0f, 1.0f}},
		{{halfSide, -halfSide,  halfSide},      {0.0f -1.0f, 0.0f},     {1.0f, 0.0f}},
		{{halfSide, -halfSide,  halfSide},      {0.0f -1.0f, 0.0f},     {1.0f, 0.0f}},
		{{-halfSide, -halfSide,  halfSide},     {0.0f -1.0f, 0.0f},     {0.0f, 0.0f}},
		{{-halfSide, -halfSide, -halfSide},     {0.0f -1.0f, 0.0f},     {0.0f, 1.0f}}, //Bottom

		{{-halfSide,  halfSide, -halfSide},     {0.0f, 1.0f, 0.0f},     {0.0f, 1.0f}},
		{{halfSide,  halfSide, -halfSide},      {0.0f, 1.0f, 0.0f},     {1.0f, 1.0f}},
		{{halfSide,  halfSide,  halfSide},      {0.0f, 1.0f, 0.0f},     {1.0f, 0.0f}},
		{{halfSide,  halfSide,  halfSide},      {0.0f, 1.0f, 0.0f},     {1.0f, 0.0f}},
		{{-halfSide,  halfSide,  halfSide},     {0.0f, 1.0f, 0.0f},     {0.0f, 0.0f}},
		{{-halfSide,  halfSide, -halfSide},     {0.0f, 1.0f, 0.0f},     {0.0f, 1.0f}}  //Top
	};

	return vertices;
}

#endif // CUBE_H
