#include "Light.h"


Light::Light(const Rgb& rgb) : SceneObject(Vector3f(0, 0, 0)), rgb(rgb)
{
}

Light::Light(const Vector3f& center, const Rgb& rgb) : SceneObject(center), rgb(rgb)
{

}


Light::~Light()
{
}

Rgb& Light::getRgb()
{
	return rgb;
}