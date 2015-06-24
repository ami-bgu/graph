#include "ObjLoader.h"

void ObjLoader::nextLine(FILE* file){
	fscanf_s(file, "%*[^\n]%*c");
}

void ObjLoader::loadOBJ(const char* path, vector<SceneObject*>& objects)
{
	printf("Loading OBJ file %s...\n", path);

	vector<Polygon*>* polygons = new vector<Polygon*>();
	vector<Vector3f> temp_vertices, temp_normals;
	vector<Vector3f> *vertices, *normals;
	Vector3f tmpVec;
	FILE* file;
	char c, firstChar, secondChar;
	int i, tmpA, tmpB;

	if (fopen_s(&file, path, "r") < 0){
		printf("Error opening object file '%s'. Exiting.\n", path);
		exit(1);
	}

	while (fscanf_s(file, "%c", &firstChar) > 0){
		switch (firstChar)
		{
			case 'v':
				fscanf_s(file, "%c", &secondChar);
				if (secondChar == 'n'){
					fscanf_s(file, " %f %f %f \n", &tmpVec.x, &tmpVec.y, &tmpVec.z);
					temp_normals.push_back(tmpVec);

				}
				else{
					fscanf_s(file, "%f %f %f \n", &tmpVec.x, &tmpVec.y, &tmpVec.z);
					temp_vertices.push_back(tmpVec);
				}

				break;

			case 'f':
				vertices = new vector<Vector3f>();
				normals = new vector<Vector3f>();

				while (fscanf_s(file, "%c", &c) > 0){
					if (c == '\n') break;

					fscanf_s(file, "%d//%d ", &tmpA,&tmpB);
					fseek(file, -1, SEEK_CUR);
					vertices->push_back(temp_vertices[tmpA-1]);
					normals->push_back(temp_normals[tmpB-1]);
				}			
				polygons->push_back(new Polygon(vertices, normals));
				
				break;

			case '\n':
				break;
			case 'o':
				if (!polygons->empty()){
					objects.push_back(new SceneObject(polygons));
					polygons = new vector<Polygon*>();
				}
			case 'g':
			case '#':
				nextLine(file);
				break;
			default:
				printf("error - unrecognized format. got: %d\n", firstChar);
				break;
		}

	}
	if (!polygons->empty()){
		objects.push_back(new SceneObject(polygons));
	}
}
