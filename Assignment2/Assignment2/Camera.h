#pragma once

#include "SceneObject.h"
#include "Plane.h"

class Camera :
	public SceneObject
{
public:
	Camera();
	Camera(const Vector3f& center, Plane* imagePlane, const Vector3f& up, const Resolution& res, const Rgb& rgb);
	virtual ~Camera();

	Resolution getResolution();

private:
	Vector3f center;
	Plane* imagePlane;
	Vector3f up;
	Resolution res;
	Rgb rgb;
};

