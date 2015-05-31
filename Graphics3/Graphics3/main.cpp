#pragma once

using namespace std;

#include "ObjLoader.h"

#include <stdio.h>
#include "GL\glut.h"

#define LINE_WIDTH 2.5

vector<SceneObject*> sceneObjects;

//GLfloat rot;
enum Mode { CAMERA_MODE, GLOBAL_MODE };
Mode _mode;
Vector3f _globalRotationAngle;
Vector3f _globalTranslation;
float _scale = 1;
float _fovAngle = 60;
int _lastClickedKey = 0;



Vector3f _cameraRotationAngle;
Vector3f _cameraTranslation;



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

Vector3f _position;
Vector3f _direction;

GLfloat _cameraRotationMatrix[16];
GLfloat _cameraTranslationMatrix[16];
GLfloat _modelRotationMatrix[16];
GLfloat _modelTranslationMatrix[16];


GLfloat _axisesMatrix[16];

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fovAngle, 1, 2, 200);
	glMatrixMode(GL_MODELVIEW);

	if (_mode == CAMERA_MODE)
	{
		//Camera Rotation
		glLoadMatrixf(_cameraRotationMatrix);
		glRotatef(_cameraRotationAngle.y*180.0, 0, 1, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, _cameraRotationMatrix);
		glRotatef(_cameraRotationAngle.x*180.0, _cameraRotationMatrix[0], _cameraRotationMatrix[4], _cameraRotationMatrix[8]);
		glGetFloatv(GL_MODELVIEW_MATRIX, _cameraRotationMatrix);

		//Camera Translation
		float transx1 = _cameraTranslation.x * _cameraRotationMatrix[0] * 50.0;
		float transy1 = _cameraTranslation.x * _cameraRotationMatrix[4] * 50.0;
		float transz1 = _cameraTranslation.x * _cameraRotationMatrix[8] * 50.0;

		float transx2 = _cameraTranslation.y * _cameraRotationMatrix[1] * 50.0;
		float transy2 = _cameraTranslation.y * _cameraRotationMatrix[5] * 50.0;
		float transz2 = _cameraTranslation.y * _cameraRotationMatrix[9] * 50.0;

		float transx3 = _cameraTranslation.z * _cameraRotationMatrix[2] * 50.0;
		float transy3 = _cameraTranslation.z * _cameraRotationMatrix[6] * 50.0;
		float transz3 = _cameraTranslation.z * _cameraRotationMatrix[10] * 50.0;

		glLoadMatrixf(_cameraTranslationMatrix);
		glTranslatef(transx1, transy1, transz1);
		glTranslatef(transx2, transy2, transz2);
		glTranslatef(transx3, transy3, transz3);
		glGetFloatv(GL_MODELVIEW_MATRIX, _cameraTranslationMatrix);
	
		_cameraTranslation.makeZero();
		_cameraRotationAngle.makeZero();
	}
	else	//GLOBAL_MODE
	{
		//Model Rotation
		glLoadMatrixf(_modelRotationMatrix);
		glRotatef(_globalRotationAngle.z*180.0, 0, 0, -1);
		glGetFloatv(GL_MODELVIEW_MATRIX, _modelRotationMatrix);
		glRotatef(_globalRotationAngle.x*180.0, _modelRotationMatrix[0], _modelRotationMatrix[4], _modelRotationMatrix[8]);
		glGetFloatv(GL_MODELVIEW_MATRIX, _modelRotationMatrix);

		//Model Translation

		float transx1 = _globalTranslation.x * _modelRotationMatrix[0] * 50.0;
		float transy1 = _globalTranslation.x * _modelRotationMatrix[4] * 50.0;
		float transz1 = _globalTranslation.x * _modelRotationMatrix[8] * 50.0;

		float transx2 = _globalTranslation.y * _modelRotationMatrix[1] * 50.0;
		float transy2 = _globalTranslation.y * _modelRotationMatrix[5] * 50.0;
		float transz2 = _globalTranslation.y * _modelRotationMatrix[9] * 50.0;

		float transx3 = _globalTranslation.z * _modelRotationMatrix[2] * 50.0;
		float transy3 = _globalTranslation.z * _modelRotationMatrix[6] * 50.0;
		float transz3 = _globalTranslation.z * _modelRotationMatrix[10] * 50.0;

		glLoadMatrixf(_modelTranslationMatrix);
		glTranslatef(transx1, transy1, transz1);
		glTranslatef(transx2, transy2, transz2);
		glTranslatef(transx3, transy3, transz3);
		glGetFloatv(GL_MODELVIEW_MATRIX, _modelTranslationMatrix);

		_globalTranslation.makeZero();
		_globalRotationAngle.makeZero();
	}


	glLoadMatrixf(_cameraRotationMatrix);
	glMultMatrixf(_cameraTranslationMatrix);
	glMultMatrixf(_modelTranslationMatrix);
	glMultMatrixf(_modelRotationMatrix);

	glScalef(_scale, _scale, _scale);

	glPushMatrix();
	glLoadMatrixf(_cameraRotationMatrix);
	glMultMatrixf(_cameraTranslationMatrix);
	glMultMatrixf(_axisesMatrix);
	drawAxises();
	glPopMatrix();

	
	//draw objects
	for (vector<SceneObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
	{
		SceneObject* object = *it;
		drawObject(*object);
	}

	glFlush(); //print to screen

}


void initLight()
{
	//lightning

	GLfloat light_direction[] = { 0, -1, -1, 1.0 };
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 }; //color
	GLfloat light_diffuse[] = { 0, 0.5, 0.5, 1.0 }; //color
	GLfloat light_specular[] = { 0, 0, 0.5, 1.0 };
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

	GLfloat mat_a[] = { 0.3, 0.4, 0.5, 1.0 };
	GLfloat mat_d[] = { 0.0, 0.6, 0.7, 1.0 };
	GLfloat mat_s[] = { 0.0, 0.0, 0.8, 1.0 };
	GLfloat low_sh[] = { 5.0 };

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

	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION); /* switch matrix mode */
	glLoadIdentity();		//load Identity matrix

	//defines view mode
	gluPerspective(60, 1, 2, 200);

	glEnable(GL_DEPTH_TEST);  //define in which order the scene will built
	/* return to modelview mode */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, _cameraRotationMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, _cameraTranslationMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, _modelRotationMatrix);

	glTranslatef(0, 0, -100);
	glGetFloatv(GL_MODELVIEW_MATRIX, _modelTranslationMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, _axisesMatrix);

	initLight();
}


int _lastClickedMouseButton;
int _lastX;
int _lastY;


void mouseGlobalMotionCallback(int x, int y){

	int x_drag_length = x - _lastX;
	int y_drag_length = y - _lastY;

	switch (_lastClickedMouseButton){
	case GLUT_LEFT_BUTTON:
		_globalRotationAngle.x += ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
		_globalRotationAngle.z += ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
		break;
	case GLUT_RIGHT_BUTTON:
		_globalTranslation.x += ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
		_globalTranslation.y -= ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
		break;
	case GLUT_MIDDLE_BUTTON:
		_globalTranslation.z -= ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
		break;
	default:
		printf("error - unsupported key\n");
	}

	_lastX = x;
	_lastY = y;
	glutPostRedisplay();
}


void mouseCameraMotionCallback(int x, int y){
	int x_drag_length = x - _lastX;
	int y_drag_length = y - _lastY;	//positive means draggin down

	switch (_lastClickedMouseButton){
	case GLUT_LEFT_BUTTON:
		_cameraRotationAngle.x += ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
		_cameraRotationAngle.y += ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
		break;
	case GLUT_RIGHT_BUTTON:
		_cameraTranslation.x -= ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
		_cameraTranslation.y += ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
		break;
	case GLUT_MIDDLE_BUTTON:
		_cameraTranslation.z -= ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
		break;
	default:
		printf("error - unsupported key\n");
	}

	_lastX = x;
	_lastY = y;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
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
	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		//switch camera on pressing SPACE
		_mode = (_mode == CAMERA_MODE) ? GLOBAL_MODE : CAMERA_MODE;
		printf("[info] Mode Changed: %s \n", printModeString());
		if (_mode == CAMERA_MODE)	glutMotionFunc(mouseCameraMotionCallback);
		else						glutMotionFunc(mouseGlobalMotionCallback);
		break;
	default:
		break;
	}
	_lastClickedKey = key;
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F2:
		_fovAngle += 0.05;
		break;
	case GLUT_KEY_F3:
		_fovAngle -= 0.05;
		break;
	case GLUT_KEY_UP:
		_scale *= 1.05;
		break;
	case GLUT_KEY_DOWN:
		_scale *= 0.95;
		break;
	default:
		break;
	}
	_lastClickedKey = key;
	glutPostRedisplay();
}

int main(int  argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment4");

	init();
	glutDisplayFunc(mydisplay);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMotionFunc(mouseCameraMotionCallback);	//changes between modes

	glutMainLoop();
}