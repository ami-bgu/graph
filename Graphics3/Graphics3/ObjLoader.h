#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Vector3f.h"
#include "SceneObject.h"


using namespace std;

class ObjLoader
{
public:
	static void splitString(const string& str, vector<string>& output);
	static void loadOBJ(const char* path, vector<SceneObject*>& objects);

};

