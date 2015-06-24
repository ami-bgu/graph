#include "SceneObject.h"


SceneObject::SceneObject(vector<Polygon*>* polygons, const Vector3f& centerOfMass)
{
	this->polygons = polygons;
	_centerOfMass = centerOfMass;
	printf("com is: [%.2f,%.2f,%.2f]\n", centerOfMass.x, centerOfMass.y, centerOfMass.z);
}


SceneObject::~SceneObject()
{
	for (vector<Polygon*>::iterator it = polygons->begin(); it != polygons->end(); ++it)
	{
		Polygon* polygon = *it;
		delete polygon;
	}
	polygons->clear();
	delete polygons;
}
