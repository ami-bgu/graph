#include "DirectionalLight.h"
#include "Shape.h"

DirectionalLight::DirectionalLight(const Vector3f& direction, const Rgb& rgb) :Light(rgb), direction(direction)
{
	this->direction.normalize();
}


DirectionalLight::~DirectionalLight()
{
}

const Vector3f DirectionalLight::getDirection(const Vector3f& point){
	return direction;
}

Rgb& DirectionalLight::getRgb()
{
	return rgb;
}

bool DirectionalLight::doesShapeDropShadowOnPoint(const Vector3f& point, Shape* shape){
	Vector3f rayFromPointToLight = direction * (-1);
	float distance = shape->rayHitDistance(point, rayFromPointToLight);
	if (distance <= 0) return false;
	
	return true;
}
