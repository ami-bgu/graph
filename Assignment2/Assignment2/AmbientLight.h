#pragma once
#include "Light.h"
class AmbientLight :
	public Light
{
public:
	AmbientLight(const Rgb& rgb);
	virtual ~AmbientLight();
};

