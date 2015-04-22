#pragma once
#include "Shape.h"

class Plane :
	public Shape
{
public:
	Plane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material);
	Plane(const Vector3f& center, const Vector3f& normal, float width, float height);

	virtual ~Plane();
	
	float getWidth();
	float getHeight();

protected:
	Vector3f normal;
	float width;
	float height;
};

