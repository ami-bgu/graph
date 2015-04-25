#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const Vector3f& direction, const Rgb& rgb);
	virtual ~DirectionalLight();
	virtual const Vector3f getDirection(const Vector3f& point);
	virtual bool doesShapeDropShadowOnPoint(const Vector3f& point, Shape* shape);

	Rgb& getRgb();
protected:
	Vector3f direction;

};

