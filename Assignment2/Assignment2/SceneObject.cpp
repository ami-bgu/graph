#include "SceneObject.h"


int SceneObject::lastId = 0;

SceneObject::SceneObject(const Vector3f& center) :center(center)
{
	this->id = (++SceneObject::lastId);
}


SceneObject::~SceneObject()
{
}


Vector3f& SceneObject::getCenter()
{
	return center;
}

int SceneObject::getId()
{
	return id;
}