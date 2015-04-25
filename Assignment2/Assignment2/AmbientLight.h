#pragma once
#include "Light.h"
class AmbientLight :
	public Light
{
public:
	AmbientLight(const Rgb& rgb);
	virtual ~AmbientLight();
	virtual const Vector3f getDirection(const Vector3f& point);

	virtual inline bool doesShapeDropShadowOnPoint(const Vector3f& point, Shape* shape) { return false; }

	virtual Rgb& getRgb();

};

