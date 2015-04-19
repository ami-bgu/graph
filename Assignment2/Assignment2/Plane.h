#pragma once
#include "Shape.h"

class Plane :
	public Shape
{
public:
	Plane(const Vector3f& center, const Vector3f& normal, int width, int height, const Material& material);
	Plane(const Vector3f& center, const Vector3f& normal, int width, int height);

	virtual ~Plane();
};

