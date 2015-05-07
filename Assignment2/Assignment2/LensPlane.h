#pragma once
#include "Plane.h"
class LensPlane :
	public Plane
{
public:
	LensPlane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material);
	LensPlane(const Vector3f& center, const Vector3f& normal, float width, float height);

	virtual ~LensPlane();

	virtual RayHitData getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes, int recursiveLevel);

};

