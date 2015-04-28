#include "Sphere.h"


Sphere::Sphere(const Vector3f& center, float radius, const Material& material) :Shape(center, material), radius(radius)
{

}


Sphere::~Sphere()
{
}

RayHitData Sphere::getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes, int recursiveLevel)
{
	if ((vec - Vector3f(0, 0, -1)).getLength() < 0.05)
	{
		int x = 5;
	}

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

		rhd.distance = t;

		if (rhd.distance <= 0)	//target is in the wrong side
		{
			rhd.isHit = false;
			return rhd;
		}


		rhd.pointOfHit = source + vec*t;

		if (rhd.pointOfHit.y > 0)
		{
			int ggg = 5;
		}

		rhd.intensity = Shape::calculateIntensity(rhd.pointOfHit, vec, ambient, lights, shapes);
		//TODO: fill rhd.directionOfNextRay
		/*
		Vector3f normalToImpact = rhd.pointOfHit - this->center;
		normalToImpact.normalize();
		Vector3f hittingRay = vec;
		hittingRay.normalize();
		Vector3f& r = (-1)*hittingRay + (normalToImpact*(2.0*Vector3f::dotProduct(hittingRay, normalToImpact)));
		*/
	}

	return rhd;
}

Vector3f Sphere::getNormal(const Vector3f& point, const Vector3f& incomingVector)
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


