#include "SceneManager.h"


SceneManager::SceneManager() :_camera(NULL)
{
}


SceneManager::~SceneManager()
{
	for (std::list<Shape*>::iterator it = _shapes.begin(); it != _shapes.end(); ++it)
	{
		delete *it;
	}
	_shapes.clear();

	for (std::list<Light*>::iterator it = _lights.begin(); it != _lights.end(); ++it)
	{
		delete *it;
	}
	_lights.clear();

	delete _camera;
}

void SceneManager::render(GLubyte* image)
{
	Resolution& res = _camera->getResolution();
	
	int size = res.width*res.height * 3;
	memset(image, 0, size);
	
	for (int i = 0; i < size/2; i++)
	{
		if (i % 3 == 0)	image[i] = 255;
		//image[i] = 255;
	}
	
	Utils::reverseArray((char*)image, size);
}

void SceneManager::init(Camera* camera)
{
	if (!_camera)
	{
		delete _camera;
		_camera = NULL;
	}
	_camera = camera;
}

void SceneManager::addSceneShape(Shape* shape)
{
	_shapes.push_back(shape);
}

void SceneManager::addSceneLight(Light* light)
{
	_lights.push_back(light);
}

Resolution SceneManager::getResolution()
{
	return _camera->getResolution();
}
