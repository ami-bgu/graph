#include "ObjLoader.h"


void ObjLoader::splitString(const string& str, vector<string>& output){
	string tmp = "";

	for (unsigned int i = 0; i<str.length(); i++){
		if (str[i] != ' ' && str[i] != ',' && str[i] != '/'){	//delimiters
			tmp = tmp + str[i];
		}
		else{
			if (tmp != "")	output.push_back(tmp);
			tmp = "";
		}
	}
	if (tmp != "")	output.push_back(tmp);
}

bool ObjLoader::loadOBJ(const char* path, vector<Polygon>& out_polygons)
{

	printf("Loading OBJ file %s...\n", path);

	vector<Vector3f> temp_vertices;
	vector<Vector3f> temp_normals;

	std::ifstream file(path);
	std::string line;
	
	while (std::getline(file, line)){
		if (line.length() == 0)	continue;
		if (line.length() >= 2 && line.compare(0, 2, "//") == 0)	continue;

		vector<string> vec;
		ObjLoader::splitString(line, vec);
		if (vec.empty())	continue;

		if (vec[0].compare(0, 2, "vn") == 0){
			Vector3f normal;
			normal.x = stof(vec[1]);
			normal.y = stof(vec[2]);
			normal.z = stof(vec[3]);
			temp_normals.push_back(normal);
		}
		else if (vec[0].compare(0, 1, "v") == 0){
			Vector3f vertex;
			vertex.x = stof(vec[1]);
			vertex.y = stof(vec[2]);
			vertex.z = stof(vec[3]);
			temp_vertices.push_back(vertex);
		}
		else if(vec[0].compare(0, 1, "f") == 0){
			vector<Vector3f> vertices;
			vector<Vector3f> normals;
			for (size_t i = 1; i < vec.size(); i+=2)
			{
				int index = stoi(vec[i]);
				vertices.push_back(temp_vertices[index - 1]);
				index = stoi(vec[i+1]);
				normals.push_back(temp_normals[index - 1]);
			}
			Polygon polygon(vertices, normals);
			out_polygons.push_back(polygon);
		}
	}

	return true;
}
