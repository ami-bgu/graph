
#pragma once

#include "Vector3f.h"


#define REFLECT_LEVEL 4
#define MIRROR_KR 0.5f



class Shape;

typedef struct Resolution
{
	int width;
	int height;
} Resolution;


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
	Shape* shape;
	RayHitData() :isHit(0) {} //empty constrcutor
} RayHitData;