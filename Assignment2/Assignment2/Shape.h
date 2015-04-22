#pragma once
#include "SceneObject.h"

class Shape :
	public SceneObject
{
public:
	Shape(const Vector3f& center, const Material& material);
	Shape(const Vector3f& center);

	virtual ~Shape();

	virtual RayHitData getRayHitResult(const Vector3f& source, const Vector3f& vec) = 0;

protected:
	Material material;

};

