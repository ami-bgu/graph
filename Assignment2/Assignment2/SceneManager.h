#pragma once

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "GL\glut.h"


#include <list>
#include "Types.h"
#include "Camera.h"
#include "Light.h"
#include "Utils.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();


	void init(Camera* camera);
	void addSceneShape(Shape* shape);
	void addSceneLight(Light* light);

	void render(GLubyte* image);
	Resolution getResolution();

private:
	Camera* _camera;
	std::list<Shape*> _shapes;
	std::list<Light*> _lights;

};

