#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const Vector3f& direction, const Rgb& rgb);
	virtual ~DirectionalLight();

protected:
	Vector3f direction;

};

