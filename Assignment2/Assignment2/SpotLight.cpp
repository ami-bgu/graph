#include "SpotLight.h"
#include "Shape.h"

SpotLight::SpotLight(const Vector3f& direction, const Rgb& rgb, const Vector3f& center, float angle) :Light(center, rgb), direction(direction), angle(angle)
{
	this->direction.normalize();
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
	Vector3f L = point - this->center;
	float d = L.getLength();
	Vector3f& D = direction;
	Rgb retVal = { 0, 0, 0 };

	float Kc = 0;
	float Kl = 1;
	float Kq = 0.1;

	float dot = Vector3f::dotProduct(D, L);
	float angleBetween = acosf( dot / (D.getLength()*L.getLength()) );
	if (abs(angleBetween) > this->angle/180){
		return retVal;
	}
	float d2 = pow(d,2);

	retVal.x		= (rgb.x   * dot) / (Kc + Kl*d + Kq*d2);
	retVal.y		= (rgb.y * dot) / (Kc + Kl*d + Kq*d2);
	retVal.z		= (rgb.z  * dot) / (Kc + Kl*d + Kq*d2);

	retVal.x		= (retVal.x   > 1) ? 1 : retVal.x;
	retVal.y		= (retVal.y > 1) ? 1 : retVal.y;
	retVal.z		= (retVal.z  > 1) ? 1 : retVal.z;
	return retVal;
}

bool SpotLight::doesShapeDropShadowOnPoint(const Vector3f& point, Shape* shape){
	Vector3f rayFromPointToLight = this->center - point;
	float distance = shape->rayHitDistance(point, rayFromPointToLight);
	
	if (distance <= 0) return false;

	if (distance > rayFromPointToLight.getLength()){
		return false;
	}
	return true;
}

bool SpotLight::doesLightComeInTheRightSide(const Vector3f& pointOfImpact, const Vector3f& normal)
{
	Vector3f& vecFromObjectToLight = pointOfImpact - this->center;
	return Vector3f::dotProduct(vecFromObjectToLight, normal) >= 0;
}
