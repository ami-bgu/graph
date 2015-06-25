#pragma once

using namespace std;

#include "ObjLoader.h"

#include <stdio.h>
#include "GL\glut.h"

#define LINE_WIDTH 2.5
#define bufSize 512
vector<SceneObject*> sceneObjects;

//GLfloat rot;
enum Mode { CAMERA_MODE, GLOBAL_MODE, PICKING_MODE };
Mode _mode;
Vector3f _globalRotationAngle;
Vector3f _globalTranslation;
float _scale = 1;
float _fovAngle = 60;
int _lastClickedKey = 0;
float _zValue[4];

vector<GLint> _selectedObjects;

vector<GLfloat> _scales;

vector<GLfloat> _xTranslations;
vector<GLfloat> _yTranslations;
vector<GLfloat> _zTranslations;

vector<GLfloat> _xRotations;
vector<GLfloat> _yRotations;
vector<GLfloat> _zRotations;

Vector3f _cameraRotationAngle;
Vector3f _cameraTranslation;

bool _isPicking = true;
bool _isTPressed = false;
bool _isRPressed = false;
bool _isSPressed = false;
GLint _lastObj = -1;

bool _inMotion = false;

char* printModeString(){
	switch (_mode)
	{
	case CAMERA_MODE:
		return "CAMERA_MODE";
	case GLOBAL_MODE:
		return "GLOBAL_MODE";
	case PICKING_MODE:
		return "PICKING_MODE";
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

SceneObject* getSceneObjectFromName(GLint name){
	for (int i = 0; i < sceneObjects.size(); i++){
		if (sceneObjects[i]->name == name){
			return sceneObjects[i];
		}
	}
	return 0;
}

bool isCurrentlySelected(vector<GLint>& selected, SceneObject& obj){
	for (int i = 0; i < selected.size(); i++){
		if (selected[i] == obj.name){
			return true;
		}
	}

	return false;
}
void drawObjects(GLenum mode){
	GLuint nameCounter = 0;
	GLfloat tempModelMatrix[16];
	Vector3f* com;

	//bonus
	if (_lastObj != -1){
		//get object from name
		for (vector<SceneObject*>::iterator it2 = sceneObjects.begin(); it2 != sceneObjects.end(); ++it2)
		{
			SceneObject* object2 = *it2;
			if (object2->name == _lastObj){
				com = &object2->_centerOfMass;
				printf("rotating around: %d \n", object2->name);

				break;
			}
		}

	}

	int i = 0;
	for (vector<SceneObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
	{
		SceneObject* object = *it;

		if (mode == GL_SELECT){
			glLoadName(nameCounter);
			object->name = nameCounter;
			nameCounter++;
		}
		
		glPushMatrix();
		//translate according to mouse
		glGetFloatv(GL_MODELVIEW_MATRIX, tempModelMatrix);

		//translate to center of mass before roatate
		if (_lastObj == -1){
			com = &object->_centerOfMass;
		}

		if (_lastObj != -1){
			SceneObject* rotateOnObj = getSceneObjectFromName(_lastObj);
			Vector3f& rotCenter = rotateOnObj->_centerOfMass;
			GLfloat* myRotMat = (*object->_rotationMatrices)[_lastObj];
			glLoadMatrixf(myRotMat);
			glTranslatef(rotCenter.x, rotCenter.y, rotCenter.z);
			//rotate
			glRotatef(_xRotations[i] * 180.0, tempModelMatrix[0], tempModelMatrix[4], tempModelMatrix[8]);
			glRotatef(_zRotations[i] * 180.0, tempModelMatrix[2], tempModelMatrix[6], tempModelMatrix[10]);
			glTranslatef(-rotCenter.x, -rotCenter.y, -rotCenter.z);
			glGetFloatv(GL_MODELVIEW_MATRIX, (*object->_rotationMatrices)[_lastObj]);
			_xRotations[i] = 0;
			_zRotations[i] = 0;
		}


		glScalef(_scales[i], _scales[i], _scales[i]);

		//translate back

		//hadnle translation
		GLfloat* myTransMat = object->_translationMatrix;
		glLoadMatrixf(myTransMat);

		glTranslatef(_xTranslations[i] * myTransMat[0] * 50.0, _xTranslations[i] * myTransMat[4] * 50.0, _xTranslations[i] * myTransMat[8] * 50.0);
		glTranslatef(_yTranslations[i] * myTransMat[1] * 50.0, _yTranslations[i] * myTransMat[5] * 50.0, _yTranslations[i] * myTransMat[9] * 50.0);
		glTranslatef(_zTranslations[i] * myTransMat[2] * 50.0, _zTranslations[i] * myTransMat[6] * 50.0, _zTranslations[i] * myTransMat[10] * 50.0);

		glGetFloatv(GL_MODELVIEW_MATRIX, object->_translationMatrix);
		//

		glLoadMatrixf(tempModelMatrix);
		glMultMatrixf(object->_translationMatrix);

		for (int m = 0; m < sceneObjects.size(); m++){
			glMultMatrixf((*object->_rotationMatrices)[m]);
		}

		drawObject(*object);

		_xTranslations[i] = 0;
		_yTranslations[i] = 0;
		_zTranslations[i] = 0;

		glPopMatrix();

		i++;
	}
}

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
	drawObjects(GL_RENDER);

	glFlush(); //print to screen

}

void addUnique(GLint name, vector<GLint>& vec){
	for (int i = 0; i < vec.size(); i++){
		if (vec[i] == name){
			return;
		}
	}

	vec.push_back(name);
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

void initObjectsTransformations(){
	for (int i = 0; i < sceneObjects.size(); i++){
		_xTranslations.push_back(0);
		_yTranslations.push_back(0);
		_zTranslations.push_back(0);
		
		_xRotations.push_back(0);
		_yRotations.push_back(0);
		_zRotations.push_back(0);

		_scales.push_back(1);
	}
}

void init()
{
	_mode = CAMERA_MODE;
	ObjLoader::loadOBJ("scene.obj", sceneObjects);	//adds objects in obj file to scene objects


	glClearColor(0, 0, 0, 1);

	//init objects matrices
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int sz = sceneObjects.size();
	
	for (int i = 0; i < sz; i++){
		for (int j = 0; j < sz; j++){
			GLfloat* tmpRotMat = new GLfloat[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, tmpRotMat);
			sceneObjects[i]->_rotationMatrices->push_back(tmpRotMat);
		}
		glGetFloatv(GL_MODELVIEW_MATRIX, sceneObjects[i]->_translationMatrix);
	}
	//end init objects matrices

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

	initObjectsTransformations();
}


int _lastClickedMouseButton;
int _lastX;
int _lastY;

void mousePickingMotionCallback(int x, int y){
	_inMotion = true;
	printf("motion func called!!!\n");
	int i;
	if (!_isPicking && (_isTPressed || _isRPressed || _isSPressed)){
		printf("moving (%d) items: \n", _selectedObjects.size());
		for (i = 0; i < _selectedObjects.size(); i++){
			printf("%d, ", _selectedObjects[i]);
		}
		//user holding left mouse button & dragging
		int x_drag_length = x - _lastX;
		int y_drag_length = y - _lastY;


		for (int i = 0; i < _selectedObjects.size(); i++)
		{
			if (_isTPressed){
				_xTranslations[_selectedObjects[i]] += ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
				_yTranslations[_selectedObjects[i]] -= ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
			}

			else if (_isRPressed){
				_xRotations[_selectedObjects[i]] += ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT);
				_zRotations[_selectedObjects[i]] += ((GLfloat)x_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_WIDTH);
			}
			else if (_isSPressed)
			{
				_scales[_selectedObjects[i]] *= ((GLfloat)y_drag_length) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) +1;
			}
		}

		_lastX = x;
		_lastY = y;
		glutPostRedisplay();

	}
	else{
		printf("still picking, picked so far: (%d) items: \n", _selectedObjects.size());
		for (i = 0; i < _selectedObjects.size(); i++){
			printf("%d, ", _selectedObjects[i]);
		}
	}


}

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
GLuint list_hits(GLint hits, GLuint *names)
{

	int i;

	/*
	For each hit in the buffer are allocated 4 bytes:
	1. Number of hits selected (always one,
	beacuse when we draw each object
	we use glLoadName, so we replace the
	prevous name in the stack)
	2. Min Z
	3. Max Z
	4. Name of the hit (glLoadName)
	*/

	/*
	printf("%d hits:\n", hits);

	for (i = 0; i < hits; i++)
		printf("Number: %d\n"
		"Min Z: %d\n"
		"Max Z: %d\n"
		"Name on stack: %d\n",
		(GLubyte)names[i * 4],
		(GLubyte)names[i * 4 + 1],
		(GLubyte)names[i * 4 + 2],
		(GLubyte)names[i * 4 + 3]
		);

	printf("\n");
	*/

	/* todo : check if we can have more than 1 */
	if (hits >= 1){
		return names[3];
	}

	return -1;
}

GLuint mousePick(int x, int y){
	GLint viewport[4];
	GLuint selectionBuf[bufSize];

	// clear selection buffer
	memset(selectionBuf, 0, sizeof(selectionBuf));

	// save current viewport
	glGetIntegerv(GL_VIEWPORT, viewport); //reading viewport parameters

	glMatrixMode(GL_PROJECTION);
	glReadPixels((GLdouble)x, (GLdouble)viewport[3] - y, 2, 2, GL_DEPTH_COMPONENT, GL_FLOAT, _zValue);

	glPushMatrix();	//saves current projection matrix
	glLoadIdentity();

	//init selection
	glSelectBuffer(bufSize, selectionBuf); //declare buffer for input in selection mode
	glRenderMode(GL_SELECT); //change to selecting mode
	glInitNames();			//initialize names stack
	glPushName(-1);			//push name

	// change viewport to be the square around the mouse click
	gluPickMatrix((GLdouble)x, (GLdouble)viewport[3] - y, 1, 1, viewport); //change matrices so only the area of the picking pixel can be seen.
	gluPerspective(_fovAngle, 1, 2, 200); //return to perspective state

	glMatrixMode(GL_MODELVIEW);
	drawObjects(GL_SELECT);

	GLint hits = glRenderMode(GL_RENDER); //gets hits number 
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); //restores projection matrix

	glMatrixMode(GL_MODELVIEW);
	return list_hits(hits, selectionBuf); //check hits

}

void mouse(int button, int state, int x, int y)
{
	if (_mode == PICKING_MODE){
		
		if (state == GLUT_DOWN && (!_isTPressed || !_isRPressed || !_isSPressed))
		{
			GLint selectedObjectName = mousePick(x, y);
			if (selectedObjectName != -1){
				if (!_isPicking){
					_selectedObjects.clear();
				}
				addUnique(selectedObjectName, _selectedObjects);

				printf("pick update: [");
				for (size_t i = 0; i < _selectedObjects.size(); i++)
				{
					printf("%d,", _selectedObjects[i]);
				}
				printf("]\n");


				if (button == GLUT_RIGHT_BUTTON)
				{
					_isPicking = true;
				}
				else if (button == GLUT_LEFT_BUTTON){
					_isPicking = false;
					_lastObj = selectedObjectName;
				}
			}
		}
		else if (state == GLUT_UP){
			if (button == GLUT_LEFT_BUTTON){
				if (_inMotion){
					_selectedObjects.clear();
					_isTPressed = false;
					_isRPressed = false;
					_isSPressed = false;
				}
			}
		}

		_inMotion = false;
	}

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
	bool changed = true;
	switch (key)
	{
	case 'g':
		_mode = GLOBAL_MODE;
		glutMotionFunc(mouseGlobalMotionCallback);

		break;
	case 'c':
		_mode = CAMERA_MODE;
		glutMotionFunc(mouseCameraMotionCallback);
		break;
	case 'p':
		glutMotionFunc(mousePickingMotionCallback);
		_mode = PICKING_MODE;
		_isTPressed = false;
		_isRPressed = false;
		_isSPressed = false;
		break;
	case 't':
		_isTPressed = true;
		changed = false;
		printf("t pressed. preparing to translate %d items\n", _selectedObjects.size());
		break;
	case 'r':
		_isRPressed = true;
		changed = false;
		printf("r pressed. preparing to rotate %d items\n", _selectedObjects.size());
		break;
	case 's':
		_isSPressed = true;
		changed = false;
		printf("s pressed. preparing to scale %d items\n", _selectedObjects.size());
		break;
	default:
		changed = false;
		break;
	}
	_lastClickedKey = key;
	if (changed){
		printf("[info] Mode Changed: %s \n", printModeString());
	}
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