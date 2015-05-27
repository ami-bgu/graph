#include "SceneObject.h"


SceneObject::SceneObject(vector<Polygon*>* polygons)
{
	this->polygons = polygons;
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
