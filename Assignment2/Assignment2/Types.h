
#pragma once

typedef struct Resolution
{
	int width;
	int height;
} Resolution;

typedef struct Rgb
{
	float red;
	float green;
	float blue;
} Rgb;

typedef struct Material
{
	Rgb Ka;
	Rgb Kd;
	Rgb Ks;
	float shininess;
	bool isMirror;
} Material;