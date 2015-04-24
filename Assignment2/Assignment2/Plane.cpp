#include "Plane.h"


Plane::Plane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material) :Shape(center, material), normal(normal), width(width), height(height)
{

}

Plane::Plane(const Vector3f& center, const Vector3f& normal, float width, float height) : Shape(center), normal(normal), width(width), height(height)
{

}

Plane::~Plane()
{
}

float Plane::getWidth()
{
	return width;
}

float Plane::getHeight()
{
	return height;
}

RayHitData Plane::getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes)
{
	RayHitData rhd;
	//calculate the point of impact in the infinite plane
	Vector3f& q0 = this->center;
	const Vector3f& p0 = source;
	Vector3f p = p0 + vec * Vector3f::dotProduct(this->normal, (q0 - p0) / Vector3f::dotProduct(this->normal, vec));
	
	//check if point of impact is in finite plane
	//TODO: finish this code


	rhd.isHit = false;
	return rhd;
}

Vector3f Plane::getNormal(const Vector3f& point)
{
	return normal;
}

float Plane::rayHitDistance(const Vector3f& source, const Vector3f& vec)
{
	//TODO: implement
	return -1;
}