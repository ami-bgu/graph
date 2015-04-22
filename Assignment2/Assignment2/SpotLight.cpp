#include "SpotLight.h"


SpotLight::SpotLight(const Vector3f& direction, const Rgb& rgb, const Vector3f& center, float angle) :Light(center, rgb), direction(direction), angle(angle)
{
}


SpotLight::~SpotLight()
{
}

const Vector3f SpotLight::getDirection(const Vector3f& point){
	//todo : implement this
	return Vector3f();
}
