#pragma once

#include <vector>
#include "Polygon.h"

using namespace std;

class SceneObject
{
public:
	SceneObject(vector<Polygon*>* polygons, const Vector3f& centerOfMass);
	~SceneObject();

	vector<Polygon*>* polygons;

	Vector3f _centerOfMass;
};

