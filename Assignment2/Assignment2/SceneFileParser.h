#pragma once

#include "SceneManager.h"
#include "Plane.h"
#include "Sphere.h"
#include "AmbientLight.h"

class SceneFileParser
{
public:

	static void parse(SceneManager& manager, const char* filename);

private:
	static void parseScene(SceneManager& manager, FILE* f1);
	static void parseLight(SceneManager& manager, FILE* f1);
	static void parseSphere(SceneManager& manager, FILE* f1);
	static void parsePlane(SceneManager& manager, FILE* f1);

	
};

