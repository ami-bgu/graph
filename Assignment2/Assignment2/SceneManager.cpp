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

/*
void SceneManager::render(GLubyte* image)
{
	Resolution& res = _camera->getResolution();
	
	int size = res.width*res.height * 3;
	memset(image, 0, size);

	for (int y = 0; y < res.height/2; y++)
	{
		for (int x = 0; x < res.width/2; x++){
			int i = res.width*y*3 + x*3;
			if (i % 3 == 0)	image[i] = 255;
		}
	}
}

*/

#define REFLECT_LEVEL 3

void SceneManager::render(GLubyte* image)
{


	vector<Vector3f> raysToImagePlane;
	_camera->calculateRaysToImagePlane(raysToImagePlane);

	Resolution res = getResolution();
	int counter= 0;
	for (int y = 0; y < res.height; y++)
	{
		for (int x = 0; x < res.width; x++){
			float min_distance = 0;
			RayHitData closestRayHit;
			bool found = false;
			for (std::list<Shape*>::iterator it_shape = _shapes.begin(); it_shape != _shapes.end(); ++it_shape)
			{
				Shape* shape = *it_shape;
				RayHitData rhd = shape->getRayHitResult(_camera->getCenter(), raysToImagePlane[y*res.width + x], _camera->getAmbientLight(), _lights, _shapes, REFLECT_LEVEL);
				if (rhd.isHit){
					found = true;
					if (min_distance == 0 || (rhd.distance>0 && rhd.distance < min_distance)){
						min_distance = rhd.distance;
						closestRayHit = rhd;
					}
				}
			}
			if (found)
			{
				image[y*res.width * 3 + (x * 3) + 0] = (GLubyte)(closestRayHit.intensity.z * 255); //B
				image[y*res.width * 3 + (x * 3) + 1] = (GLubyte)(closestRayHit.intensity.y * 255); //G
				image[y*res.width * 3 + (x * 3) + 2] = (GLubyte)(closestRayHit.intensity.x * 255); //R
			}
			else
			{
				image[y*res.width * 3 + (x * 3) + 0] = (GLubyte)0; //B
				image[y*res.width * 3 + (x * 3) + 1] = (GLubyte)0; //G
				image[y*res.width * 3 + (x * 3) + 2] = (GLubyte)0; //R
			}
			counter++;

		}
	}
	//printf("counter is : %d\n", counter);
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
