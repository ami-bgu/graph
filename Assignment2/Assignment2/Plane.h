#pragma once
#include "Shape.h"

class Plane :
	public Shape
{
public:
	Plane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material);
	Plane(const Vector3f& center, const Vector3f& normal, float width, float height);

	virtual ~Plane();
	
	virtual RayHitData getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, std::list<Light*>& lights);

	float getWidth();
	float getHeight();

protected:
	Vector3f normal;
	float width;
	float height;

};

