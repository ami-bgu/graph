#pragma once

#include "Vector3f.h"

class Triangle
{
public:

	//vertices must me array of size 3
	Triangle(const Vector3f* vertices, const Vector3f& normal);

	~Triangle();

	Vector3f vertices[3];
	Vector3f normal;


};

