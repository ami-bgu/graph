
#pragma once

#include "Vector3f.h"

typedef struct Resolution
{
	int width;
	int height;
} Resolution;

/*
typedef struct Rgb
{
	float red;
	float green;
	float blue;
} Rgb;
*/
typedef Vector3f Rgb;

typedef struct Material
{
	Rgb Ka;
	Rgb Kd;
	Rgb Ks;
	float shininess;
	bool isMirror;
} Material;

typedef struct RayHitData
{
	Vector3f pointOfHit;
	Vector3f directionOfNextRay;
	Rgb intensity;
	float distance;
	bool isHit;
} RayHitData;