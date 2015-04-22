#pragma once
#include "Light.h"
class AmbientLight :
	public Light
{
public:
	AmbientLight(const Rgb& rgb);
	virtual ~AmbientLight();
	virtual const Vector3f getDirection(const Vector3f& point);

	virtual Rgb& getRgb();

};

