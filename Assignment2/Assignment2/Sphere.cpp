#include "Sphere.h"


Sphere::Sphere(const Vector3f& center, float radius, const Material& material) :Shape(center, material), radius(radius)
{

}


Sphere::~Sphere()
{
}

RayHitData Sphere::getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes)
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
		rhd.pointOfHit = source + vec*t;
		rhd.distance = t;
		rhd.intensity = Shape::calculateIntensity(rhd.pointOfHit, ambient, lights, shapes);
		//TODO: fill rhd.directionOfNextRay
	}

	return rhd;
}

Vector3f Sphere::getNormal(const Vector3f& point)
{
	Vector3f normal = point - center;
	normal.normalize();
	return normal;
}

float Sphere::rayHitDistance(const Vector3f& source, const Vector3f& vec1)
{
	Vector3f vec = vec1;
	vec.normalize();
	float retDistance;
	Vector3f l = this->center - source;
	float tm = Vector3f::dotProduct(l, vec);
	float dsqr = Vector3f::dotProduct(l, l) - (tm*tm);
	float rsqr = this->radius * this->radius;
	if (dsqr > rsqr)
	{
		//retDistance = -1;
		return 0;
	}
	else
	{
		float th = sqrt(rsqr - dsqr);
		float t1 = tm - th;
		float t2 = tm + th;
		float t = t1 > 0 ? t1 : t2;

		return t;
		//return (tm + th); //todo: why this?
	}
}


