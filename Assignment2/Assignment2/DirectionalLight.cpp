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

bool DirectionalLight::doesLightComeInTheRightSide(const Vector3f& pointOfImpact, const Vector3f& normal)
{
	//above the shapes' surface is true
	return Vector3f::dotProduct(direction*(-1), normal) >= 0;
}
