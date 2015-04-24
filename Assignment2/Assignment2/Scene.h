#pragma once
#include "AmbientLight.h"
#include "Shape.h"
#include "Light.h"
#include "Camera.h"
#include <list>

class Scene
{
public:
	Scene();
	~Scene();

private:
	Camera* _camera;
	AmbientLight* ambient;
	std::list<Shape*> _shapes;
	std::list<Light*> _lights;	//spot & directional
	
};

