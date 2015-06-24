#pragma once

#include <vector>
#include "Polygon.h"

using namespace std;

class SceneObject
{
public:
	SceneObject(vector<Polygon*>* polygons);
	~SceneObject();

	vector<Polygon*>* polygons;

};

