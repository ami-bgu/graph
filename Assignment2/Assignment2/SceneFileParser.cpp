#include "SceneFileParser.h"


void SceneFileParser::parseScene(SceneManager& manager, FILE* f1)
{
	//for scene formatting
	float Px, Py, Pz;
	float UPx, UPy, UPz;
	float width;
	int screen_x, screen_y;
	float ambient_light_R, ambient_light_G, ambient_light_B;

	printf("\nscene");

	fscanf_s(f1, "%f,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f,%f\r\n",
		&Px, &Py, &Pz, &UPx, &UPy, &UPz, &width, &screen_x, &screen_y,
		&ambient_light_R, &ambient_light_G, &ambient_light_B);

	printf("\n\tCenter:\t(%.2f,%.2f,%.2f) \n\tUp:\t(%.2f,%.2f,%.2f) \n\tWidth:\t(%.2f) \n\tScreen:\t%dx%d \n\tAmbient Light:\t(%.2f,%.2f,%.2f)\n",
		Px, Py, Pz, UPx, UPy, UPz, width, screen_x, screen_y,
		ambient_light_R, ambient_light_G, ambient_light_B);

//	Plane(const Vector3f& center, const Vector3f& normal, int width, int height);

	Vector3f cameraPos(0, 0, 0);
	Vector3f& imagePlaneCenter = Vector3f(Px, Py, Pz);
	Vector3f& normal = (imagePlaneCenter - cameraPos);
	normal.normalize();
	Plane* imagePlane = new Plane(imagePlaneCenter, normal, width, width);

	//Camera(const Vector3f& center, const Plane& imagePlane, const Vector3f& up, int resolutionX, int resolutionY, const float* rgb);
	Rgb ambient = { ambient_light_R, ambient_light_G, ambient_light_B };
	Resolution res = { screen_x, screen_y };
	Camera* camera = new Camera(cameraPos, imagePlane, Vector3f(UPx, UPy, UPz), res, ambient);

	manager.init(camera);
}

void SceneFileParser::parseLight(SceneManager& manager, FILE* f1)
{

}

void SceneFileParser::parseSphere(SceneManager& manager, FILE* f1)
{
	//for spher formatting
	float spher_x, spher_y, spher_z;
	float spher_radius;
	float Ka_R, Ka_G, Ka_B;
	float Kd_R, Kd_G, Kd_B;
	float Ks_R, Ks_G, Ks_B;
	float shininess;

	printf("\nsphere");

	fscanf_s(f1, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n",
		&spher_x, &spher_y, &spher_z, &spher_radius, &Ka_R, &Ka_G, &Ka_B, &Kd_R, &Kd_G, &Kd_B, &Ks_R, &Ks_G, &Ks_B, &shininess);

	printf("\n\tCenter:\t(%.2f,%.2f,%.2f) \n\tRadius:\t(%.2f) \n\tKa:\t(%.2f,%.2f,%.2f) \n\tKd:\t(%.2f,%.2f,%.2f) \n\tKs:\t(%.2f,%.2f,%.2f) \n\tShininess:\t%.2f \n",
		spher_x, spher_y, spher_z, spher_radius, Ka_R, Ka_G, Ka_B, Kd_R, Kd_G, Kd_B, Ks_R, Ks_G, Ks_B, shininess);

	//	Sphere(const Vector3f& center, float radius, const Material& material);

	Rgb ka_rgb = { Ka_R, Ka_G, Ka_B };
	Rgb kd_rgb = { Kd_R, Kd_G, Kd_B };
	Rgb ks_rgb = { Ks_R, Ks_G, Ks_B };
	Material material = { ka_rgb, kd_rgb, ks_rgb, shininess, false };
	Sphere* sphere = new Sphere(Vector3f(spher_x, spher_y, spher_z), spher_radius, material);

	manager.addSceneShape(sphere);
}

//TODO: support shininess
void SceneFileParser::parsePlane(SceneManager& manager, FILE* f1)
{
	//for plane
	float plane_normal_x, plane_normal_y, plane_normal_z;
	float plane_center_x, plane_center_y, plane_center_z;
	float plane_width, plane_height;

	float plane_Ka_R, plane_Ka_G, plane_Ka_B;
	float plane_Kd_R, plane_Kd_G, plane_Kd_B;
	float plane_Ks_R, plane_Ks_G, plane_Ks_B;

	printf("\nplane");

	fscanf_s(f1, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n",
		&plane_normal_x, &plane_normal_y, &plane_normal_z, &plane_center_x, &plane_center_y, &plane_center_z, &plane_width, &plane_height,
		&plane_Ka_R, &plane_Ka_G, &plane_Ka_B, &plane_Kd_R, &plane_Kd_G, &plane_Kd_B, &plane_Ks_R, &plane_Ks_G, &plane_Ks_B);

	printf("\n\tNormal:\t(%.2f,%.2f,%.2f) \n\tCenter:\t(%.2f,%.2f,%.2f) \n\tWidth:\t%.2f \n\tHeight:\t%.2f \n\tKa:\t(%.2f,%.2f,%.2f) \n\tKd:\t(%.2f,%.2f,%.2f) \n\tKs:\t(%.2f,%.2f,%.2f)\n",
		plane_normal_x, plane_normal_y, plane_normal_z, plane_center_x, plane_center_y, plane_center_z, plane_width, plane_height,
		plane_Ka_R, plane_Ka_G, plane_Ka_B, plane_Kd_R, plane_Kd_G, plane_Kd_B, plane_Ks_R, plane_Ks_G, plane_Ks_B);

	//	Plane(const Vector3f& center, const Vector3f& normal, int width, int height, const Material& material);
	Rgb ka_rgb = { plane_Ka_R, plane_Ka_G, plane_Ka_B };
	Rgb kd_rgb = { plane_Kd_R, plane_Kd_G, plane_Kd_B };
	Rgb ks_rgb = { plane_Ks_R, plane_Ks_G, plane_Ks_B };
	Material material = { ka_rgb, kd_rgb, ks_rgb , 0, false };
	Plane* plane = new Plane(Vector3f(plane_center_x, plane_center_y, plane_center_z), Vector3f(plane_normal_x, plane_normal_y, plane_normal_z), plane_width, plane_height, material);

	manager.addSceneShape(plane);
}

void SceneFileParser::parse(SceneManager& manager, const char* filename)
{
	FILE* f1;
	int rd;
	char type[6];
	type[5] = 0;
	char* SCENE = "scene";
	char* LIGHT = "light";
	char* SPHER = "spher";
	char* PLANE = "plane";
//	float var;
	int pos = 0;
	char c;

	//for light formatting
	float light_dir_x, light_dir_y, light_dir_z;
	float light_intensity_R, light_intensity_G, light_intensity_B;
	float spot_x, spot_y, spot_z;
	int cutoff_angle;



	printf("Input file: %s \n", filename);

	fopen_s(&f1, filename, "rb");

	for (int i = 0; i < 5; i++)
	{
		rd = fread(type, 1, 5, f1); //read type

		if (strcmp(type, SCENE) == 0){
			SceneFileParser::parseScene(manager, f1);
		}
		else if (strcmp(type, LIGHT) == 0){
			//light 1,1,1,0.3,0.2,0.6
			//OR if spotlight:
			//light 1,-1,1,0.9,0.1,0.6,0,4,-5.5,30

			printf("\nlight");

			fscanf_s(f1, "%f,%f,%f,%f,%f,%f", &light_dir_x, &light_dir_y, &light_dir_z, &light_intensity_R, &light_intensity_G, &light_intensity_B);

			printf("\n\tDirection\t(%.1f,%.1f,%.1f) \n\tIntensity:\t(%.1f,%.1f,%.1f)",
				light_dir_x, light_dir_y, light_dir_z, light_intensity_R, light_intensity_G, light_intensity_B);

			rd = fread(&c, 1, 1, f1); //read next char
			if (c == ','){ //spot light
				fscanf_s(f1, "%f,%f,%f,%d\n", &spot_x, &spot_y, &spot_z, &cutoff_angle);
				printf("\n\tSpotlight position:\t(%.1f,%.1f,%.1f) \n\tCutoff Angle:\t%d\n", spot_x, spot_y, spot_z, cutoff_angle);
			}
			else{ //regular light we just read \r so we reed \n too
				rd = fread(&c, 1, 1, f1); //read next char
				printf("\n");
			}

		}
		else if (strcmp(type, SPHER) == 0){
			SceneFileParser::parseSphere(manager, f1);

		}
		else if (strcmp(type, PLANE) == 0){
			SceneFileParser::parsePlane(manager, f1);
		}
		else{
			printf("Error: I can't recognize this: %s \n Exiting...", type);
			exit(1);
		}
	}
	fclose(f1);

}