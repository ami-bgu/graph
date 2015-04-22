#pragma once

#include "SceneObject.h"
#include "Plane.h"
#include "AmbientLight.h"
#include "Utils.h"

class Camera :
	public SceneObject
{
public:
	Camera(const Vector3f& center, Plane* imagePlane, const Vector3f& up, const Resolution& res, const AmbientLight& ambient);
	virtual ~Camera();
	Resolution getResolution();
	void calculateRaysToImagePlane(vector<Vector3f>& rays);


private:
	//vector<Vector3f>& raysToImagePlane;
	Plane* imagePlane;
	Vector3f up;
	Resolution res;
	AmbientLight ambient;

};

