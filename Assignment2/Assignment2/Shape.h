#pragma once
#include "SceneObject.h"

class Shape :
	public SceneObject
{
public:
	Shape();
	virtual ~Shape();

private:
	Material material;

};

