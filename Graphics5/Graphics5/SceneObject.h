#pragma once

#include <vector>
#include "Polygon.h"
#include "GL\glut.h"

using namespace std;

class SceneObject
{
public:
	SceneObject(vector<Polygon*>* polygons, const Vector3f& centerOfMass);
	~SceneObject();

	vector<Polygon*>* polygons;
	GLint name;
	Vector3f _centerOfMass;
};

