#pragma once
#include "SceneObject.h"
class Light :
	public SceneObject
{
public:
	Light(const Rgb& rgb);
	Light(const Vector3f& center, const Rgb& rgb);
	virtual ~Light();
	virtual Rgb getRgb(const Vector3f& point);
	virtual const Vector3f getDirection(const Vector3f& point) = 0;


protected:
	Rgb rgb;
	Vector3f direction;
};

