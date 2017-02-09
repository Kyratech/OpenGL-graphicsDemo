#ifndef PLANE_H
#define PLANE_H

#include "Introduction.h"

const std::vector<struct Vertex> GetPlaneGeometry()
{
    const std::vector<struct Vertex> vertices = {
		{{-0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // Bottom left
		{{0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},  // Bottom Right
		{{-0.5f, 0.5f, 0.0f},   {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},  // Top Left
		{{0.5f, 0.5f, 0.0f},    {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},	// Top right
		{{-0.5f, 0.5f, 0.0f},   {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},  // Top Left
		{{0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}  // Bottom Right
	};

	return vertices;
}

#endif // PLANE_H
