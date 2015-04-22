#pragma once

#include <stdio.h>
#include <math.h>
#include "Vector3f.h"
#include "Types.h"

class SceneObject
{
public:
	SceneObject(const Vector3f& center);
	virtual ~SceneObject();
	Vector3f& getCenter();

protected:
	Vector3f center;
};

