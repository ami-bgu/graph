#include "Camera.h"

Camera::Camera()
{


}

Camera::Camera(const Vector3f& center, Plane* imagePlane, const Vector3f& up, const Resolution& res, const Rgb& rgb) :
					center(center), imagePlane(imagePlane), up(up), res(res), rgb(rgb)
{

}


Camera::~Camera()
{
	delete imagePlane;
}

Resolution Camera::getResolution()
{
	return res;
}
