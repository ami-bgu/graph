#include "SceneObject.h"


SceneObject::SceneObject(const Vector3f& center) :center(center)
{
}


SceneObject::~SceneObject()
{
}


Vector3f& SceneObject::getCenter()
{
	return center;
}