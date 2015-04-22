#pragma once
#include "Light.h"
class SpotLight :
	public Light
{
public:
	SpotLight(const Vector3f& direction, const Rgb& rgb, const Vector3f& center, float angle);
	virtual ~SpotLight();

protected:
	Vector3f direction;
	float angle;
};

