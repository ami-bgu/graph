#pragma once
#include "Light.h"
class AmbientLight :
	public Light
{
public:
	AmbientLight(const float(&rgb)[3]);
	virtual ~AmbientLight();
};

