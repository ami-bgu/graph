#include "SpotLight.h"


SpotLight::SpotLight(const Vector3f& direction, const Rgb& rgb, const Vector3f& center, float angle) :Light(center, rgb), direction(direction), angle(angle)
{
}


SpotLight::~SpotLight()
{
}

const Vector3f SpotLight::getDirection(const Vector3f& point){
	//todo : implement this
	return direction;
}

Rgb SpotLight::getRgb(const Vector3f& point)
{
	Vector3f L = point-this->center;
	Vector3f& D = direction;

	float Kc = 0;
	float Kl = 1;
	float Kq = 1;

	float dot = Vector3f::dotProduct(D, L);
	float d = L.getLength();
	float d2 = pow(d,2);

	Rgb retVal;
	retVal.red = (rgb.red * dot) / (Kc + Kl*d + Kq*d2);
	retVal.green = (rgb.green * dot) / (Kc + Kl*d + Kq*d2);
	retVal.blue = (rgb.blue * dot) / (Kc + Kl*d + Kq*d2);

	retVal.red = (retVal.red > 1) ? 1 : retVal.red;
	retVal.green = (retVal.green > 1) ? 1 : retVal.green;
	retVal.blue = (retVal.blue > 1) ? 1 : retVal.blue;
	return retVal;
}