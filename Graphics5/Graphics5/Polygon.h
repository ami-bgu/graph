#pragma once

#include <vector>
#include "Vector3f.h"

using namespace std;

class Polygon
{
public:

	//vertices must me array of size 3
	Polygon(vector<Vector3f>* vertices, vector<Vector3f>* normals);

	~Polygon();

	vector<Vector3f>* vertices;
	vector<Vector3f>* normals;


};

