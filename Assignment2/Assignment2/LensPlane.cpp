#include "LensPlane.h"



LensPlane::LensPlane(const Vector3f& center, const Vector3f& normal, float width, float height, const Material& material) :Plane(center, normal, width, height, material)
{

}
LensPlane::LensPlane(const Vector3f& center, const Vector3f& normal, float width, float height) :Plane(center, normal, width, height)
{

}

LensPlane::~LensPlane()
{
}


RayHitData LensPlane::getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes, int recursiveLevel)
{
	RayHitData data = Plane::getRayHitResult(source, vec, ambient, lights, shapes, recursiveLevel);

	Vector3f& myvec = vec * (-1);
	myvec.normalize();
	Vector3f& normal = getNormal(data.pointOfHit, myvec);
	float angleOfHit = acosf(Vector3f::dotProduct(myvec, normal));


	
	float r = (this->center - data.pointOfHit).getLength();

	float thetha = r* M_PI / 2.0;	//thetha is aperture/2
	float phi = 2.0*M_PI;		//phi is between 0 to 2PI

	data.directionOfNextRay =  vec * Vector3f(sin(thetha)*cos(phi),
										sin(thetha)*sin(phi),
										cos(thetha));
	return data;
}
