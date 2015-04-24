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

Rgb Shape::calculateIntensity(const Vector3f& pointOfImpact, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes)
{
	//add ie

	//ambient light
	Rgb retVal;
	Rgb ia = ambient.getRgb();
	retVal.red		= ia.red	* material.Ka.red;
	retVal.green	= ia.green	* material.Ka.green;
	retVal.blue		= ia.blue	* material.Ka.blue;
	
	//TODO: add occlusion & shadows
	//diffuse + specular
	Rgb rgb = { 0, 0, 0 };
	for (std::list<Light*>::iterator it = lights.begin(); it != lights.end(); ++it)
	{
		Light* light = *it;

		//check if occluded
		bool isOccluded = false;
		/*
		//for each shape check
		for (std::list<Shape*>::iterator s_it = shapes.begin(); s_it != shapes.end(); ++s_it){
			Shape* shape = *s_it;
			if (shape == this) continue; //skip if its the same shape
			float shapeDistanceFromLight = light->getDirection() - ;
			float myDistanceFromLight;
			if (shapeDistanceFromLight == -1) continue; //shape is not in the way
			
			if (shape->doesRayHit(pointOfImpact, light->getDirection() )){
				isOccluded = true;
				break;
			}
		}*/
		if (isOccluded) continue;

		//diffuse
		Vector3f& normal = getNormal(pointOfImpact);
		const Vector3f& li = light->getDirection(pointOfImpact)*(-1);
		float tmpNxL = Vector3f::dotProduct(normal, li);
		if (tmpNxL<=0) continue;
		rgb.red		+= tmpNxL * material.Kd.red;
		rgb.green	+= tmpNxL * material.Kd.green;
		rgb.blue	+= tmpNxL * material.Kd.blue;
	
		//specluar
		Vector3f& v = Vector3f(0, 0, 0) - pointOfImpact;	//TODO: change 0,0,0 to camera center
		v.normalize();
		Vector3f& r = (-1)*li + (normal*(2.0*Vector3f::dotProduct(li, normal)));
		float spec = powf(Vector3f::dotProduct(v, r),material.shininess);
		rgb.red		+= spec * material.Ks.red;
		rgb.green	+= spec * material.Ks.green;
		rgb.blue	+= spec * material.Ks.blue;
		
		//add intensity
		retVal.red		+= rgb.red*light->getRgb(pointOfImpact).red;
		retVal.green	+= rgb.green*light->getRgb(pointOfImpact).green;
		retVal.blue		+= rgb.blue*light->getRgb(pointOfImpact).blue;
	}

	//1 is max intensity
	retVal.red		= (retVal.red    > 1) ? 1 : retVal.red;
	retVal.green	= (retVal.green  > 1) ? 1 : retVal.green;
	retVal.blue		= (retVal.blue   > 1) ? 1 : retVal.blue;
	return retVal;
}