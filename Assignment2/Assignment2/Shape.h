#pragma once
#include "SceneObject.h"

class Shape :
	public SceneObject
{
public:
	Shape(const Vector3f& center, const Material& material);
	Shape(const Vector3f& center);

	virtual ~Shape();

protected:
	Material material;

};

