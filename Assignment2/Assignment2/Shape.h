#pragma once
#include "SceneObject.h"
#include "AmbientLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"


class Shape :
	public SceneObject
{
public:
	Shape(const Vector3f& center, const Material& material);
	Shape(const Vector3f& center);

	virtual ~Shape();

	virtual RayHitData getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes, int recursiveLevel) = 0;
	virtual float rayHitDistance(const Vector3f& source, const Vector3f& vec) = 0;

	inline Material& getMaterial() { return material; }

protected:
	Material material;
	virtual Vector3f getNormal(const Vector3f& point, const Vector3f& incomingVector) = 0;
	virtual Rgb calculateIntensity(const Vector3f& pointOfImpact, const Vector3f& incomingRay, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes);

	virtual Vector3f getReflectedRay(const Vector3f& pointOfImpact, const Vector3f& incomingRay);

private:
	bool isOccluded(const Vector3f& pointOfImpact, const Vector3f& rayDirection, std::vector<Shape*>& shapes);
};

