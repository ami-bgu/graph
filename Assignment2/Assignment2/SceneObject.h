#pragma once

#include <stdio.h>
#include <math.h>
#include "Vector3f.h"
#include "Types.h"

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();


private:
	Vector3f center;
};

