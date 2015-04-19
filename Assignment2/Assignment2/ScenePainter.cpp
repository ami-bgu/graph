#include "ScenePainter.h"


GLuint ScenePainter::texture;
GLubyte* ScenePainter::pic;
Resolution ScenePainter::resolution;

void ScenePainter::writeArrayToFile(char questionNum, GLubyte* content, int size)
{
	char filename[30];
	strcpy_s(filename, "assignment\\imgX.txt");
	filename[14] = questionNum;
	FILE* pFile;
	CreateDirectory("assignment", NULL);
	fopen_s(&pFile, filename, "wb");

	for (int i = 0; i < size; i++)
	{
		int value = content[i] / 16;
		char str[4];
		_itoa_s(value, str, 10);
		fwrite(str, sizeof(char)*strlen(str), 1, pFile);

		if (i < size - 1)	fwrite(",", sizeof(char), 1, pFile);
	}
	
	fclose(pFile);
}

void ScenePainter::applyImageToTexture()
{
	
	glGenTextures(1, &texture);  //generate place for new texture
	glBindTexture(GL_TEXTURE_2D, texture); // initialize first texure 

	//texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//build texture
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.width, resolution.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pic);	//original
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.width, resolution.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pic);	//best	

	
}

void ScenePainter::init()
{
	
	glEnable(GL_TEXTURE_2D);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, -2.0);
	glClearColor(0, 0, 0, 0);

	applyImageToTexture();

	//writeArrayToFile('1', pic, resolution.width*resolution.height);
	
}


void ScenePainter::paintQuadWithTexture(GLint x, GLint y, GLsizei width, GLsizei height, GLuint textureKey)
{
	glViewport(x, y, width, height);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textureKey); //using first texture

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); //adapt texture to shape
	glVertex3f(-1.0, -1.0f, 1.0);

	glTexCoord2f(1, 0);  //adapt texture to shape
	glVertex3f(1.0, -1.0f, 1.0);

	glTexCoord2f(1, 1);//adapt texture to shape
	glVertex3f(1.0, 1.0f, 1.0);

	glTexCoord2f(0, 1);//adapt texture to shape
	glVertex3f(-1.0, 1.0f, 1.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ScenePainter::mydisplay(void){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	paintQuadWithTexture(0, 0, ScenePainter::resolution.width, ScenePainter::resolution.height, texture);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFlush();
}

void ScenePainter::paintToScreen(GLubyte* pic1, const Resolution& resolution1)
{
	ScenePainter::resolution = resolution1;
	ScenePainter::pic = pic1;

	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ScenePainter::resolution.width, ScenePainter::resolution.height);
	glutCreateWindow("Assignment2");

	init();
	glutDisplayFunc(ScenePainter::mydisplay);
	glutMainLoop();

}