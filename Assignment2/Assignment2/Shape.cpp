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

Rgb Shape::calculateIntensity(const Vector3f& pointOfImpact, const Vector3f& incomingRay, AmbientLight& ambient, list<Light*>& lights, list<Shape*>& shapes)
{
	if ((incomingRay - Vector3f(0, 0, -1)).getLength() < 0.05)
	{
		int x = 5;
	}

	Rgb retVal(0,0,0);

	//ambient light
	if (!material.isTransparent)
	{
		Rgb ia = ambient.getRgb();
		retVal = ia * material.Ka;
	}
	
	//TODO: add occlusion & shadows
	//diffuse + specular
	Rgb rgb(0,0,0);
	for (std::list<Light*>::iterator it = lights.begin(); it != lights.end(); ++it)
	{
		Light* light = *it;
		const Vector3f& li = light->getDirection(pointOfImpact)*(-1);
		Vector3f& normal = getNormal(pointOfImpact, li);
		if (!light->doesLightComeInTheRightSide(pointOfImpact, normal))	continue;
		//check if occluded
		bool isOccluded = false;
		
		//for each shape check
		for (std::list<Shape*>::iterator s_it = shapes.begin(); s_it != shapes.end(); ++s_it){
			Shape* shape = *s_it;
			if (shape == this) continue; //skip if its the same shape
			
			if (light->doesShapeDropShadowOnPoint(pointOfImpact,shape)){
				isOccluded = true;
				break;
			}
			
		}
		if (isOccluded) continue;

		//diffuse
		float tmpNxL = Vector3f::dotProduct(normal, li);
		if (tmpNxL <= 0) continue;
		rgb += material.Kd*tmpNxL;
		

		//specluar
		Vector3f& v = Vector3f(0, 0, 0) - pointOfImpact;	//TODO: change 0,0,0 to source
		v.normalize();
		Vector3f& r = (-1)*li + (normal*(2.0*Vector3f::dotProduct(li, normal)));
		float spec = powf(Vector3f::dotProduct(v, r), material.shininess);
		rgb += material.Ks*spec;
		
		//add intensity
		retVal += rgb * light->getRgb(pointOfImpact);
	}

	//1 is max intensity
	retVal.x		= (retVal.x    > 1) ? 1 : retVal.x;
	retVal.y	= (retVal.y  > 1) ? 1 : retVal.y;
	retVal.z		= (retVal.z   > 1) ? 1 : retVal.z;
	return retVal;
}

Vector3f Shape::getReflectedRay(const Vector3f& pointOfImpact, const Vector3f& incomingRay)
{
	Vector3f li = incomingRay*(-1);
	Vector3f& normal = getNormal(pointOfImpact, incomingRay);
	Vector3f& r = (-1)*li + (normal*(2.0*Vector3f::dotProduct(li, normal)));
	return r;
}
