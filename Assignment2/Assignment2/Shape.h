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

	virtual Rgb calculateIntensity(AmbientLight& ambient, std::list<Light*>& lights);

};

