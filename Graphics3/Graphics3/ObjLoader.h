#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Vector3f.h"
#include "Polygon.h"


using namespace std;

class ObjLoader
{
public:
	static void splitString(const string& str, vector<string>& output);
	static bool loadOBJ(const char* path, vector<Polygon>& out_polygons);

};

