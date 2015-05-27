#pragma once

using namespace std;

#include "ObjLoader.h"

#include <stdio.h>
#include "GL\glut.h"

#define LINE_WIDTH 2.5

vector<SceneObject*> sceneObjects;

GLfloat rot;
enum Mode { CAMERA_MODE, GLOBAL_MODE};
Mode _mode;
Vector3f globalRotationAngle;


char* printModeString(){
	switch (_mode)
	{
	case CAMERA_MODE:
		return "CAMERA_MODE";
	case GLOBAL_MODE:
		return "GLOBAL_MODE";
	default:
		return "UNDEFINED!";
	}
}

//drawing a <width> width line of color <color> from <begin> to <end>
void drawLine(Vector3f& color, Vector3f& begin, Vector3f& end, GLfloat width){
	glColor3f(color.x, color.y, color.z);
	glLineWidth(width);

	glBegin(GL_LINES);
		glVertex3f(begin.x, begin.y, begin.z);
		glVertex3f(end.x, end.y, end.z);
	glEnd();
}

//drawing our axis
void drawAxises()
{
	GLfloat w = 2.5;
	Vector3f red = Vector3f(1, 0, 0);
	Vector3f green = Vector3f(0, 0, 1);
	Vector3f blue = Vector3f(0, 1, 0);

	glDisable(GL_LIGHTING);

	// X axis
	drawLine(red, Vector3f(-50, 0, 0), Vector3f(50, 0, 0), w);
	// Y axis
	drawLine(green, Vector3f(0, -50, 0), Vector3f(0, 50, 0), w);
	// Z axis
	drawLine(blue, Vector3f(0, 0, -50), Vector3f(0, 0, 50), w);

	glEnable(GL_LIGHTING);
}

void drawPolygon(Polygon& polygon)
{
	vector<Vector3f>& normals = *(polygon.normals);
	vector<Vector3f>& vertices = *(polygon.vertices);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < polygon.vertices->size(); i++)
	{
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
}


void drawObject(SceneObject& object)
{
	for (std::vector<Polygon*>::iterator it = object.polygons->begin(); it != object.polygons->end(); ++it)
	{
		Polygon* polygon = *it;
		drawPolygon(*polygon);
	}


}

void globalRotate()
{
	printf("rotating: %.2f,%.2f,%.2f\n", globalRotationAngle.x, globalRotationAngle.y, globalRotationAngle.z);
	glRotatef(10,
		globalRotationAngle.x,
		globalRotationAngle.y,
		globalRotationAngle.z
		);

	globalRotationAngle.makeZero();
}

void mydisplay()
{
	printf("mydisplay\n");
	GLfloat light_position[]={0,0,3,1};
	GLfloat light_direction[]={0,0,-1};
	GLfloat emission[] ={0,0,1};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	//glRotatef(rot,0,1,0); //rotate scene
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	//draw axises
	drawAxises();

	for (vector<SceneObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
	{
		SceneObject* object = *it;
		drawObject(*object);
	}
	

	//globalRotate();
	/*
	//draws a purple square on the back wall
//	drawSquare(Vector3f(0.3,0,0.3));

	//draws a green triangle on the ceiling
	glPushMatrix();
	glRotatef(90,1,0,0);
	
//	drawTriangle(Vector3f(0.0,.5,0),Vector3f(0,-1,0));
	glPopMatrix();
	
	//draws a white sphere in the midle
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glutSolidSphere(0.5,32,32);

	//draws cube
	glMaterialfv(GL_FRONT, GL_EMISSION, Vector3f(1,1,1));
	glutWireCube(2.0f);
	*/
	glFlush(); //print to screen
	
}


void initLight()
{
	//lightning
	
	GLfloat light_direction[]={0,-1,-1,1.0};
	GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0}; //color
	GLfloat light_diffuse[] = {0, 0.5, 0.5, 1.0}; //color
	GLfloat light_specular[] = {0, 0, 0.5, 1.0}; 
	//GLfloat light_position[]={-0.0,-1.5,1,0,0.0};
	//GLfloat angle[] = {20.0};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	//glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF,angle);
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat mat_a[] = {0.3, 0.4, 0.5, 1.0};
	GLfloat mat_d[] = {0.0, 0.6, 0.7, 1.0};
	GLfloat mat_s[] = {0.0, 0.0, 0.8, 1.0};
	GLfloat low_sh[] = {5.0};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_sh);
	
//	glEnable(GL_COLOR_MATERIAL);
//	glDisable(GL_LIGHTING);

}


void init()
{
	_mode = CAMERA_MODE;
	ObjLoader::loadOBJ("doll.obj", sceneObjects);	//adds objects in obj file to scene objects

	float modelMatrix[16],projectionMatrix[16];
	glClearColor(0,0,0,1);
	
	glMatrixMode(GL_PROJECTION); /* switch matrix mode */
	glLoadIdentity();		//load Identity matrix

	//defines view mode
	gluPerspective(60,1,2,200);
	//glRotatef(180,0,1,0);
	glTranslatef(0,0,-100);	//take camera backwards
	
	//glTranslatef(0,1,0);
	//gluLookAt(0,-1,-1,0,-2,-2,1,1,0);  //define view direction
	//gluLookAt(0,-1,-1,0,0,0,1,1,0);  //define view direction
	

	glEnable(GL_DEPTH_TEST);  //define in which order the scene will built
	 /* return to modelview mode */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	rot=0.01;
	initLight();
}


int _lastClickedMouseButton;
int _lastX;
int _lastY;


void mouseMotionCallback(int x, int y){
	//printf("[Event=mouse motion] (%d,%d) \n", x, y);
	int x_drag_length = x - _lastX;
	int y_drag_length = y - _lastY;
	//printf("last x: %d, x: %d, distance: %d \n", _lastX, x, x_drag_length);
	//printf("last y: %d, x: %d, distance: %d \n", _lastY, y, y_drag_length);
	//printf("screen width:%d, screen height:%d \n", glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	switch (_lastClickedMouseButton){
		case GLUT_LEFT_BUTTON:
			//printf("rotating camera x_length:%f, y_length: %f", ((float)y_drag_length) / (float)glutGet(GLUT_WINDOW_WIDTH), ((float)x_drag_length) / (float)glutGet(GLUT_WINDOW_HEIGHT));
			globalRotationAngle.y += ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
			break;
			
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			printf("error - unsupported key\n");
	}
	
	_lastX = x;
	_lastY = y;
	//glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	printf("[Event=mouse] state: %d (%d,%d) \n", state,x,y);


	switch (state)
	{
	case GLUT_DOWN:
		_lastClickedMouseButton = button;
		_lastX = x;
		_lastY = y;
		break;
	case GLUT_UP:
		_lastClickedMouseButton = 0;
		break;
	default:
		break;
	}

/*	if (_mode == CAMERA_MODE){
		mouseCameraModeHandler(button, state, x, y);
	}
	else if (_mode == GLOBAL_MODE){
		mouseGlobalModeHandler(button, state, x, y);
	}
*/
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	//switch camera on pressing SPACE
	case ' ':
		_mode = (_mode == CAMERA_MODE) ? GLOBAL_MODE : CAMERA_MODE;
		printf("[info] Mode Changed: %s \n", printModeString());
		break;
	default:
		break;
	}
}

void specialKeys(int key, int x, int y)
{
	printf("special:%d;", key);
}

int main(int  argc,  char** argv) 
{
   glutInit (& argc, argv) ;
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB) ;
   glutInitWindowSize (512,512) ;
   glutCreateWindow("Assignment4");
  
   init();
   glutDisplayFunc(mydisplay);   

   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeys);
   glutMotionFunc(mouseMotionCallback);
   
   glutMainLoop();
}