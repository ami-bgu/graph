#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(const Vector3f& direction, const Rgb& rgb) :Light(rgb), direction(direction)
{
}


DirectionalLight::~DirectionalLight()
{
}
