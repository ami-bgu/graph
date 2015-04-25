#include "Plane.h"


Plane::Plane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material) :Shape(center, material), normal(normal), width(width), height(height)
{
	calculateCorners();
}

Plane::Plane(const Vector3f& center, const Vector3f& normal, float width, float height) : Shape(center), normal(normal), width(width), height(height)
{
	calculateCorners();
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
	//todo: check what happen if the plane is parallel 

	rhd.isHit = true;
	int arr[8] = { 0, 1, 1, 2, 2, 3, 3, 0 };

	for (int i = 0; i < 8; i+=2){
		Vector3f V1 = corners[i] - source;
		Vector3f V2 = corners[1+1] - source;
		Vector3f V1xV2 = Vector3f::crossProduct(V1, V2);

		Vector3f N = V1xV2 / V1xV2.getLength();
		Vector3f minusv = (p - p0);
		if (Vector3f::dotProduct(minusv, N) < 0){
			rhd.isHit = false;
			return rhd;
		}
		
	}

	//if (!rhd.isHit) return rhd;

	rhd.pointOfHit = p;
	rhd.distance = (p - p0).getLength();
	rhd.intensity = Shape::calculateIntensity(p, ambient, lights, shapes);

	return rhd;
}

Vector3f Plane::getNormal(const Vector3f& point)
{
	return normal;
}

float Plane::rayHitDistance(const Vector3f& source, const Vector3f& vec)
{
	//todo: simplifiy .. this is a copy paste..
	RayHitData rhd;
	//calculate the point of impact in the infinite plane
	Vector3f& q0 = this->center;
	const Vector3f& p0 = source;
	Vector3f p = p0 + vec * Vector3f::dotProduct(this->normal, (q0 - p0) / Vector3f::dotProduct(this->normal, vec));
	//todo: check what happen if the plane is parallel 

	rhd.isHit = false;
	int arr[8] = { 0, 1, 1, 2, 2, 3, 3, 0 };

	for (int i = 0; i < 8; i += 2){
		Vector3f V1 = corners[i] - source;
		Vector3f V2 = corners[1 + 1] - source;
		Vector3f V1xV2 = Vector3f::crossProduct(V1, V2);
		Vector3f N = V1xV2 / V1xV2.getLength();

		if (Vector3f::dotProduct((p - p0), N) >= 0){
			rhd.isHit = true;
		}
	}

	if (!rhd.isHit) return 0;

	rhd.distance = (p - p0).getLength();

	return rhd.distance;
}

void Plane::calculateCorners()
{
	Vector3f horizontalDirection;
	Vector3f verticalDirection;
	normal.getTwoOrthogonals(horizontalDirection, verticalDirection);
	horizontalDirection.normalize();
	verticalDirection.normalize();
	horizontalDirection *= width / 2;
	verticalDirection *= height / 2;

	corners[0] = center + (horizontalDirection + verticalDirection);
	corners[1] = center + ( (horizontalDirection*(-1)) + verticalDirection);
	corners[2] = center + (horizontalDirection + (verticalDirection*(-1)) );
	corners[3] = center + ( (horizontalDirection*(-1)) + (verticalDirection*(-1)) );
}
