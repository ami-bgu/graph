#pragma once
#include "Shape.h"
class Sphere :
	public Shape
{
public:

	Sphere(const Vector3f& center, float radius, const Material& material);

	virtual ~Sphere();
};

