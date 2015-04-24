#pragma once

#include <stdio.h>
#include <math.h>
#include "Vector3f.h"
#include "Types.h"
#include <list>
#include <vector>
using namespace std;

class SceneObject
{
public:
	SceneObject(const Vector3f& center);
	virtual ~SceneObject();
	Vector3f& getCenter();
	int getId();
protected:
	Vector3f center;

private:
	int id;
	static int lastId;

};

