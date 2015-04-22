#pragma once
#include "SceneObject.h"
class Light :
	public SceneObject
{
public:
	Light(const Rgb& rgb);
	Light(const Vector3f& center, const Rgb& rgb);
	virtual ~Light();

protected:
	Rgb rgb;
};

