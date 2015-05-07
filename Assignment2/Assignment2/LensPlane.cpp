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

	///////////PASTE
	Vector3f& N = normal;
	Vector3f& I = myvec;
	float ki = 2.0f, kr = 1.0f; // for air and water
	float r = ki / kr, r2 = r*r;
	float invr = kr / ki, invr2 = invr*invr;

	float ndoti, two_ndoti, ndoti2, a, b, b2, D2;
	Vector3f T;
	ndoti = N.x*I.x + N.y*I.y + N.z*I.z;     // 3 mul, 2 add
	ndoti2 = ndoti*ndoti;                    // 1 mul
	if (ndoti >= 0.0) { b = r; b2 = r2; }
	else { b = invr; b2 = invr2; }
	D2 = 1.0f - b2*(1.0f - ndoti2);

	if (D2 >= 0.0f) {
		if (ndoti >= 0.0f)
			a = b * ndoti - sqrtf(D2); // 2 mul, 3 add, 1 sqrt
		else
			a = b * ndoti + sqrtf(D2);
		T.x = a*N.x - b*I.x;     // 6 mul, 3 add
		T.y = a*N.y - b*I.y;     // ----totals---------
		T.z = a*N.z - b*I.z;     // 12 mul, 8 add, 1 sqrt!
	}
	else {
		// total internal reflection
		// this usually doesn't happen, so I don't count it.
		two_ndoti = ndoti + ndoti;         // +1 add
		T.x = two_ndoti * N.x - I.x;      // +3 adds, +3 muls
		T.y = two_ndoti * N.y - I.y;
		T.z = two_ndoti * N.z - I.z;
	}
	data.directionOfNextRay = T;

	return data;
}
