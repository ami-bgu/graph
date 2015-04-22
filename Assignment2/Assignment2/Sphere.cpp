#include "Sphere.h"


Sphere::Sphere(const Vector3f& center, float radius, const Material& material) :Shape(center, material), radius(radius)
{

}


Sphere::~Sphere()
{
}

RayHitData Sphere::getRayHitResult(const Vector3f& source, const Vector3f& vec)
{
	RayHitData rhd;

	Vector3f l = this->center - source;
	float tm = Vector3f::dotProduct(l, vec);
	float dsqr = Vector3f::dotProduct(l, l) - (tm*tm);
	float rsqr = this->radius * this->radius;

	if (dsqr > rsqr)
	{
		rhd.isHit = false;
	}
	else
	{
		rhd.isHit = true;
		float th = sqrt(rsqr - dsqr);
		float t1 = tm - th;
		float t2 = tm + th;
		float t = t1 > 0 ? t1 : t2;
		Rgb rgb = { 1.0, 1.0, 1.0 };
		rhd.pointOfHit = source + vec*t;
		rhd.distance = t;
		rhd.intensity = rgb;
		//TODO: fill rhd.directionOfNextRay
	}

	return rhd;
}