#include "DirectionalLight.h"


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