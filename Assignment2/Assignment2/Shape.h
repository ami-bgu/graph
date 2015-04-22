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

	virtual RayHitData getRayHitResult(const Vector3f& source, const Vector3f& vec, AmbientLight& ambient, std::list<Light*>& lights) = 0;

protected:
	Material material;
	virtual Vector3f getNormal(const Vector3f& point) = 0;
	virtual Rgb calculateIntensity(const Vector3f& pointOfImpact, AmbientLight& ambient, std::list<Light*>& lights);

private:
	bool isOccluded(const Vector3f& pointOfImpact, const Vector3f& rayDirection, std::vector<Shape*>& shapes);
};

