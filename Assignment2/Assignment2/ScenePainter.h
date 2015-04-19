#pragma once

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "GL\glut.h"

#include "SceneFileParser.h"

class ScenePainter
{
public:

	void paintToScreen(GLubyte* pic1, const Resolution& resolution);


private:
	void writeArrayToFile(char questionNum, GLubyte* content, int size);
	void applyImageToTexture();
	void init();
	static void paintQuadWithTexture(GLint x, GLint y, GLsizei width, GLsizei height, GLuint textureKey);
	static void mydisplay(void);


	static GLuint texture;
	static GLubyte* pic;
	static Resolution resolution;

};

