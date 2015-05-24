#pragma once

#include <vector>
#include "Vector3f.h"
#include "Triangle.h"


using namespace std;

class ObjLoader
{
public:
	static bool loadOBJ(const char* path, vector<Triangle>& out_triangles);

};

