#include "Triangle.h"


Triangle::Triangle(const Vector3f* vertices, const Vector3f& normal)
{
	for (size_t i = 0; i < 3; i++)
	{
		this->vertices[i] = vertices[i];
	}
	this->normal = normal;
}




Triangle::~Triangle()
{
}
