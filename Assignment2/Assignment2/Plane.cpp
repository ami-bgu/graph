#include "Plane.h"


Plane::Plane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material) :Shape(center, material), normal(normal), width(width), height(height)
{

}

Plane::Plane(const Vector3f& center, const Vector3f& normal, float width, float height) : Shape(center), normal(normal), width(width), height(height)
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

Plane::~Plane()
{
}
