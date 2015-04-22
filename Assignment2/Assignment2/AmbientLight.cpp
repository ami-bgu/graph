#include "AmbientLight.h"


AmbientLight::AmbientLight(const Rgb& rgb) :Light(rgb)
{
}


AmbientLight::~AmbientLight()
{
}

const Vector3f AmbientLight::getDirection(const Vector3f& point){
	//wont call this ever
	printf("you shouldnt call this ");
	return Vector3f();
}

Rgb& AmbientLight::getRgb()
{
	return rgb;
}
