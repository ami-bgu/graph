#include "Shape.h"


Shape::Shape(const Vector3f& center, const Material& material) :SceneObject(center), material(material)
{
}

Shape::Shape(const Vector3f& center) : SceneObject(center)
{
}


Shape::~Shape()
{
}

Rgb Shape::calculateIntensity(const Vector3f& pointOfImpact, AmbientLight& ambient, std::list<Light*>& lights)
{
	//add ie

	//ambient light
	Rgb retVal;
	Rgb ia = ambient.getRgb();
	retVal.red = ia.red*material.Ka.red;
	retVal.green = ia.green*material.Ka.green;
	retVal.blue = ia.blue*material.Ka.blue;
	
	//directional light
	Rgb rgb = { 0, 0, 0 };
	for (std::list<Light*>::iterator it = lights.begin(); it != lights.end(); ++it)
	{
		Light* light = *it;
		Vector3f normal = getNormal(pointOfImpact);
		const Vector3f& li = light->getDirection(pointOfImpact);
		float tmpNxL = Vector3f::dotProduct(normal, li);
		rgb.red += (tmpNxL >= 0) ? tmpNxL * material.Kd.red : 0;
		rgb.green += (tmpNxL >= 0) ? tmpNxL * material.Kd.green : 0;
		rgb.blue += (tmpNxL >= 0) ? tmpNxL * material.Kd.blue : 0;

		//Vector3f& v = pointOfImpact - Vector3f(0, 0, 0);	//TODO: change 0,0,0 to camera center
		retVal.red += rgb.red*light->getRgb().red;
		retVal.green += rgb.green*light->getRgb().green;
		retVal.blue += rgb.blue*light->getRgb().blue;
	}

	//1 is max blat
	retVal.red = (retVal.red  > 1) ? 1 : retVal.red;
	retVal.green = (retVal.green  > 1) ? 1 : retVal.green;
	retVal.blue = (retVal.blue  > 1) ? 1 : retVal.blue;
	return retVal;
}