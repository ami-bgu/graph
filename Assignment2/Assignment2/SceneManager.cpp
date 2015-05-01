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

//thetha is aperture/2
//phi is between 0 to 2PI
Vector3f calculateImagePlaneMapping(float thetha, float phi)
{
	return Vector3f(	sin(thetha)*cos(phi),
						sin(thetha)*sin(phi),
						cos(thetha)				);
}


RayHitData SceneManager::rayHit(const Vector3f& source, const Vector3f& vec, Shape* lastShape, int recursionLevel)
{
	RayHitData closestRayHit;
	if (recursionLevel > 0)
	{
		float min_distance = 0;
		bool found = false;

		//get ray hit data of closest shape
		for (std::list<Shape*>::iterator it_shape = _shapes.begin(); it_shape != _shapes.end(); ++it_shape)
		{
			Shape* shape = *it_shape;
			if (lastShape == shape)	continue;
			RayHitData rhd = shape->getRayHitResult(source, vec, _camera->getAmbientLight(), _lights, _shapes, recursionLevel);
			if (rhd.isHit){
				found = true;
				if (min_distance == 0 || (rhd.distance > 0 && rhd.distance < min_distance)){
					min_distance = rhd.distance;
					closestRayHit = rhd;
				}
			}
		}
		//recursion
		if (recursionLevel > 1 && closestRayHit.isHit && closestRayHit.shape->getMaterial().isMirror)
		{
			RayHitData nextHit = rayHit(closestRayHit.pointOfHit, closestRayHit.directionOfNextRay, closestRayHit.shape, recursionLevel - 1);
			if (nextHit.isHit)
			{
				//closestRayHit.intensity += (nextHit.intensity * MIRROR_KR);
				//closestRayHit.intensity.x = (closestRayHit.intensity.x    > 1) ? 1 : closestRayHit.intensity.x;
				//closestRayHit.intensity.y = (closestRayHit.intensity.y  > 1) ? 1 : closestRayHit.intensity.y;
				//closestRayHit.intensity.z = (closestRayHit.intensity.z   > 1) ? 1 : closestRayHit.intensity.z;
				closestRayHit.intensity = nextHit.intensity;
			}
		}
	}
	return closestRayHit;
}



void SceneManager::render(GLubyte* image)
{


	vector<Vector3f> raysToImagePlane;
	_camera->calculateRaysToImagePlane(raysToImagePlane);

	Resolution res = getResolution();
	int counter= 0;
	for (int y = 0; y < res.height; y++)
	{
		for (int x = 0; x < res.width; x++){
			RayHitData closestRayHit = rayHit(_camera->getCenter(), raysToImagePlane[y*res.width + x], 0, REFLECT_LEVEL);

			if (closestRayHit.isHit)
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
			counter++;	//for debug

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
