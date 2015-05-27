#include "Polygon.h"


Polygon::Polygon(vector<Vector3f>* vertices, vector<Vector3f>* normals)
{
	this->vertices = vertices;
	this->normals = normals;
}




Polygon::~Polygon()
{
	vertices->clear();
	normals->clear();
	delete vertices;
	delete normals;
}
