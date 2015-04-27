#pragma once
#include "Shape.h"
class Sphere :
	public Shape
{
public:

	Sphere(const Vector3f& center, float radius, const Material& material);
	virtual ~Sphere();

	virtual RayHitData getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes, int recursiveLevel);

	virtual float rayHitDistance(const Vector3f& source, const Vector3f& vec);



protected:
	virtual Vector3f getNormal(const Vector3f& point, const Vector3f& incomingVector);

	float radius;
};

