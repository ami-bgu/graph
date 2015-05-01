#include "SceneFileParser.h"


void SceneFileParser::parseScene(SceneManager& manager, vector<string>& vec)
{
	//for scene formatting
	float Px	= stof(vec[1]);
	float Py	= stof(vec[2]);
	float Pz	= stof(vec[3]);
	float UPx	= stof(vec[4]);
	float UPy	= stof(vec[5]);
	float UPz	= stof(vec[6]);
	float width = stof(vec[7]);
	int screen_x = stod(vec[8]);
	int screen_y = stod(vec[9]);
	float ambient_light_R = stof(vec[10]);
	float ambient_light_G = stof(vec[11]);
	float ambient_light_B = stof(vec[12]);

	printf("\nscene");

	printf("\n\tCenter:\t(%.2f,%.2f,%.2f) \n\tUp:\t(%.2f,%.2f,%.2f) \n\tWidth:\t(%.2f) \n\tScreen:\t%dx%d \n\tAmbient:\t(%.2f,%.2f,%.2f)\n",
		Px, Py, Pz, UPx, UPy, UPz, width, screen_x, screen_y,
		ambient_light_R, ambient_light_G, ambient_light_B);

//	Plane(const Vector3f& center, const Vector3f& normal, int width, int height);

	Vector3f cameraPos(0, 0, 0);
	Vector3f& imagePlaneCenter = Vector3f(Px, Py, Pz);
	Vector3f& normal = (imagePlaneCenter - cameraPos);
	normal.normalize();
	float height = width * (float)screen_y / (float)screen_x;
	Plane* imagePlane = new Plane(imagePlaneCenter, normal, width, height);

	//Camera(const Vector3f& center, const Plane& imagePlane, const Vector3f& up, int resolutionX, int resolutionY, const float* rgb);
	Rgb ambient_rgb = { ambient_light_R, ambient_light_G, ambient_light_B };
	Resolution res = { screen_x, screen_y };
	Camera* camera = new Camera(cameraPos, imagePlane, Vector3f(UPx, UPy, UPz), res, AmbientLight(ambient_rgb));

	manager.init(camera);
}

void SceneFileParser::parseLight(SceneManager& manager, vector<string>& vec)
{
	//for light formatting

	Light* light = NULL;
	float light_dir_x = stof(vec[1]);
	float light_dir_y = stof(vec[2]);
	float light_dir_z = stof(vec[3]);
	float light_intensity_R = stof(vec[4]);
	float light_intensity_G = stof(vec[5]);
	float light_intensity_B = stof(vec[6]);
	printf("\nlight");
	printf("\n\tDirection\t(%.1f,%.1f,%.1f) \n\tIntensity:\t(%.1f,%.1f,%.1f)",
		light_dir_x, light_dir_y, light_dir_z, light_intensity_R, light_intensity_G, light_intensity_B);
	Rgb rgb = { light_intensity_R, light_intensity_G, light_intensity_B };
	if (vec.size() > 7)	//spot light
	{
		float spot_x = stof(vec[7]);
		float spot_y = stof(vec[8]);
		float spot_z = stof(vec[9]);
		float cutoff_angle = stof(vec[10]);
		printf("\n\tSpotlight pos:\t(%.2f,%.2f,%.2f) \n\tCutoff Angle:\t%.2f\n", spot_x, spot_y, spot_z, cutoff_angle);
		light = new SpotLight(Vector3f(light_dir_x,light_dir_y,light_dir_z),rgb,Vector3f(spot_x,spot_y,spot_z),cutoff_angle);	//TODO: fill constructors
	}
	else //directional light
	{
		light = new DirectionalLight(Vector3f(light_dir_x, light_dir_y, light_dir_z), rgb); //TODO: fill constructors
	}
	manager.addSceneLight(light);
}

Material SceneFileParser::parseMaterial(SceneManager& manager, vector<string>& vec)
{
	
	float Ka_R = stof(vec[1]);
	float Ka_G = stof(vec[2]);
	float Ka_B = stof(vec[3]);

	float Kd_R = stof(vec[4]);
	float Kd_G = stof(vec[5]);
	float Kd_B = stof(vec[6]);

	float Ks_R = stof(vec[7]);
	float Ks_G = stof(vec[8]);
	float Ks_B = stof(vec[9]);

	float shininess = stof(vec[10]);

	bool M = false;	//mirror
	bool T = false; //transparent
	bool L = false; //lens

	for (size_t i = 11; i < vec.size(); i++)
	{
		char c = vec[i].at(0);
		switch (c)
		{
		case 'M':
			M = true;
			break;
		case 'T':
			T = true;
			break;
		case 'L':
			L = true;
			break;
		}
	}


	printf("\tMaterial:\tKa:\t(%.2f,%.2f,%.2f)\n\t\t\tKd:\t(%.2f,%.2f,%.2f)\n\t\t\tKs:\t(%.2f,%.2f,%.2f)\n\t\t\tShininess:\t%.2f\n\t\t\tSpecial:M-%d,T-%d,L-%d\n", Ka_R, Ka_G, Ka_B, Kd_R, Kd_G, Kd_B, Ks_R, Ks_G, Ks_B, shininess, M, T,L);
	
	Rgb ka_rgb = { Ka_R, Ka_G, Ka_B };
	Rgb kd_rgb = { Kd_R, Kd_G, Kd_B };
	Rgb ks_rgb = { Ks_R, Ks_G, Ks_B };
	Material material = { ka_rgb, kd_rgb, ks_rgb, shininess, M,T,L };
	return material;

}


void SceneFileParser::parseSphere(SceneManager& manager, vector<string>& vec)
{
	
	//for spher formatting
	float spher_x = stof(vec[1]);
	float spher_y = stof(vec[2]);
	float spher_z = stof(vec[3]);
	float spher_radius = stof(vec[4]);;

	printf("\nsphere");

	printf("\n\tCenter:\t(%.2f,%.2f,%.2f)\n\tRadius:\t(%.2f)\n", spher_x, spher_y, spher_z, spher_radius);

	//	Sphere(const Vector3f& center, float radius, const Material& material);

	vec.erase(vec.begin(), vec.begin() + 4);

	Material& material = SceneFileParser::parseMaterial(manager, vec);
	Sphere* sphere = new Sphere(Vector3f(spher_x, spher_y, spher_z), spher_radius, material);

	manager.addSceneShape(sphere);
	
}

//TODO: support shininess
void SceneFileParser::parsePlane(SceneManager& manager, vector<string>& vec)
{
	
	//for plane
	float plane_normal_x = stof(vec[1]);
	float plane_normal_y = stof(vec[2]);
	float plane_normal_z = stof(vec[3]);
	float plane_center_x = stof(vec[4]);
	float plane_center_y = stof(vec[5]);
	float plane_center_z = stof(vec[6]);
	float plane_width = stof(vec[7]);
	float plane_height = stof(vec[8]);

	printf("\nplane");

	printf("\n\tNormal:\t(%.2f,%.2f,%.2f) \n\tCenter:\t(%.2f,%.2f,%.2f) \n\tWidth:\t%.2f \n\tHeight:\t%.2f\n",
		plane_normal_x, plane_normal_y, plane_normal_z, plane_center_x, plane_center_y, plane_center_z, plane_width, plane_height);

	//	Plane(const Vector3f& center, const Vector3f& normal, int width, int height, const Material& material);
	vec.erase(vec.begin(), vec.begin() + 8);

	Material& material = SceneFileParser::parseMaterial(manager, vec);
	Plane* plane;
	if (material.isLens)
	{
		plane = new LensPlane(Vector3f(plane_center_x, plane_center_y, plane_center_z), Vector3f(plane_normal_x, plane_normal_y, plane_normal_z), plane_width, plane_height, material);
	}
	else
	{
		plane = new Plane(Vector3f(plane_center_x, plane_center_y, plane_center_z), Vector3f(plane_normal_x, plane_normal_y, plane_normal_z), plane_width, plane_height, material);

	}

	manager.addSceneShape(plane);
	
}

void SceneFileParser::parse(SceneManager& manager, const char* filename)
{
	char type[6];
	type[5] = 0;
	char* SCENE = "scene";
	char* LIGHT = "light";
	char* SPHER = "spher";
	char* PLANE = "plane";
	int i = 0;
	printf("Input file: %s \n", filename);

	std::istringstream infile(filename);

	
	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line))
	{
		if (line.length() == 0)	continue;
		if (line.length() >= 2 && line.compare(0,2,"//")==0)	continue;

		vector<string> vec;
		Utils::splitString(line, vec);
		if (vec.empty())	continue;
		if (vec[0].compare(0,5,SCENE) == 0){
			SceneFileParser::parseScene(manager, vec);
		}
		else if (vec[0].compare(0, 5, LIGHT) == 0){
			SceneFileParser::parseLight(manager, vec);

		}
		else if (vec[0].compare(0, 5, SPHER) == 0){
			SceneFileParser::parseSphere(manager, vec);

		}
		else if (vec[0].compare(0, 5, PLANE) == 0){
			SceneFileParser::parsePlane(manager, vec);
		}
		else{
			printf("Error: I can't recognize this: %s \n Exiting...", type);
			exit(1);
		}

	}
}