#include "Camera.h"



Camera::Camera(const Vector3f& center, Plane* imagePlane, const Vector3f& up, const Resolution& res, const AmbientLight& ambient) :
SceneObject(center), imagePlane(imagePlane), up(up), res(res), ambient(ambient)
{
	this->up.normalize();	//have to be normalized
//	raysToImagePlane = new Vector3f[res.width*res.height];

}


Camera::~Camera()
{
	delete imagePlane;
	//delete[] raysToImagePlane;
}

Resolution& Camera::getResolution()
{
	return res;
}

AmbientLight& Camera::getAmbientLight()
{
	return ambient;
}

//TODO: check if we can optimize with calculating just half
void Camera::calculateRaysToImagePlane(vector<Vector3f>& raysToImagePlane)
{
	Vector3f& pc = imagePlane->getCenter();
	Vector3f towards = pc - this->center;
	Vector3f right = Vector3f::crossProduct(towards, this->up);
	float r = imagePlane->getWidth() / ((float)res.width);
	right.normalize();

	Utils::set2DArraySizes(res.width, res.height);

	int half_rx = (res.width) / 2;
	int half_ry = (res.height) / 2;
	for (int y = 0; y < res.height ; y++)
	{
		for (int x = 0; x < res.width; x++)
		{
			Vector3f p = pc + right*((x - half_rx)*(float)r) - up*((y - half_ry)*(float)r);
			Vector3f ray = p - this->center;
			ray.normalize();
			raysToImagePlane.push_back(ray);
			//raysToImagePlane[Utils::get1DIndexFrom2D(x, y)] = ray;
		}
	}

}