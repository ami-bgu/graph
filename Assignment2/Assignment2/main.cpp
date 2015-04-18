#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "GL\glut.h"

void init(const char* filename)
{
	FILE* f1;
	int rd;
	GLubyte header[54], colorTable[1024];
	glEnable(GL_TEXTURE_2D);
	glOrtho(-1.0, 1.0, -1.0, 1.0, 2.0, -2.0);
	glClearColor(0, 0, 0, 0);

	fopen_s(&f1, filename, "rb");

	/*************************/
	//image header reading
	fread(header, 54, 1, f1);
	if (header[0] != 'B' || header[1] != 'M')		exit(1);  //not a BMP file

	original_width = *(int*)(header + 18);
	original_height = *(int*)(header + 22);
	printf("\nlena %d %d %d \n", original_width, original_height, original_width*original_height);

	/**********************************/

	originalPic = new GLubyte[original_width*original_height];
	newPics[F_NONE] = originalPic;
	newPics[F_SOBEL] = new GLubyte[original_width*original_height];
	newPics[F_HALFTONE] = new GLubyte[original_height*original_width * 4];
	newPics[F_FLOYD] = new GLubyte[original_width*original_height];

	rd = fread(colorTable, 1, 1024, f1); //read color table
	rd = fread(originalPic, 1, original_width*original_height, f1); //read image

	fclose(f1);


	applyFilterToTexture(F_NONE, NULL, original_width, original_height);
	applyFilterToTexture(F_SOBEL, sobel, original_width, original_height);
	applyFilterToTexture(F_HALFTONE, halftone, original_width * 2, original_height * 2);
	applyFilterToTexture(F_FLOYD, floyd, original_width, original_height);

	writeArrayToFile('4', newPics[F_SOBEL], original_width*original_height, TRUE);
	writeArrayToFile('5', newPics[F_HALFTONE], original_width*original_height * 4, TRUE);
	writeArrayToFile('6', newPics[F_FLOYD], original_width*original_height, FALSE);
}

int main(int  argc, char** argv)
{
	if (argc < 2){
		printf("Please specify a filename. \n Exiting..");
		getc(stdin);
		exit(1);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment1");

	init(argv[1]);
	glutDisplayFunc(mydisplay);
	glutMainLoop();

	//delete[] newPics;
}