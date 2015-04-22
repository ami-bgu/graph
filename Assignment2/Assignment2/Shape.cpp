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

Rgb Shape::calculateIntensity(AmbientLight& ambient, std::list<Light*>& lights)
{
	Rgb retVal;
	Rgb ia = ambient.getRgb();
	retVal.red = ia.red*material.Ka.red;
	retVal.green = ia.green*material.Ka.green;
	retVal.blue = ia.blue*material.Ka.blue;
	//todo add sigma and Ie
	return retVal;
}