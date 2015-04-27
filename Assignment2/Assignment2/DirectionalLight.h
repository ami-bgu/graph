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

	virtual bool doesLightComeInTheRightSide(const Vector3f& pointOfImpact, const Vector3f& vectorFromPrevObject);


	Rgb& getRgb();
protected:
	Vector3f direction;

};

