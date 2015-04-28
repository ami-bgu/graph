#pragma once
#include "SceneObject.h"

class Shape;

class Light :
	public SceneObject
{
public:
	Light(const Rgb& rgb);
	Light(const Vector3f& center, const Rgb& rgb);
	virtual ~Light();
	virtual Rgb getRgb(const Vector3f& point);
	virtual const Vector3f getDirection(const Vector3f& point) = 0;

	virtual bool doesShapeDropShadowOnPoint(const Vector3f& point, Shape* shape)  = 0;

	virtual inline bool doesLightComeInTheRightSide(const Vector3f& pointOfImpact, const Vector3f& normal){ return true; }

protected:
	Rgb rgb;
	Vector3f direction;
};

