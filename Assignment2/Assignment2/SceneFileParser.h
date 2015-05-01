#pragma once

#include "SceneManager.h"
#include "LensPlane.h"
#include "Sphere.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"


#include <vector>
#include <string>
#include <sstream>
#include <fstream>



class SceneFileParser
{
public:

	static void parse(SceneManager& manager, const char* filename);

private:
	static Material parseMaterial(SceneManager& manager, vector<string>& vec);
	static void parseScene(SceneManager& manager, vector<string>& vec);
	static void parseLight(SceneManager& manager, vector<string>& vec);
	static void parseSphere(SceneManager& manager, vector<string>& vec);
	static void parsePlane(SceneManager& manager, vector<string>& vec);

	
};

