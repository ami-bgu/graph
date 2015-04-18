#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "GL\glut.h"
#include <stdlib.h>


void init(const char* filename)
{
	FILE* f1;
	int rd;
	char type[6];
	type[5] = 0;
	char* SCENE = "scene";
	char* LIGHT = "light";
	char* SPHER = "spher";
	char* PLANE = "plane";
	float var;
	int pos=0;
	char c;

	//for scene formatting
	int Px, Py, Pz;
	int UPx, UPy, UPz;
	int width_x, width_y, width_z;
	int screen_x, screen_y;
	float ambient_light_a, ambient_light_b, ambient_light_c, ambient_light_d, ambient_light_e, ambient_light_f;

	//for light formatting
	float light_dir_x, light_dir_y, light_dir_z;
	float light_intensity_R, light_intensity_G, light_intensity_B;
	float spot_x, spot_y, spot_z;
	int cutoff_angle;

	//for spher formatting
	int spher_x, spher_y, spher_z;
	float spher_radius;
	float Ka_R, Ka_G, Ka_B;
	float Kd_R, Kd_G, Kd_B;
	float Ks_R, Ks_G, Ks_B;
	int shininess;

	//for plane
	float plane_normal_x, plane_normal_y, plane_normal_z;
	int plane_center_x, plane_center_y, plane_center_z;
	int plane_width, plane_height;

	float plane_Ka_R, plane_Ka_G, plane_Ka_B;
	float plane_Kd_R, plane_Kd_G, plane_Kd_B;
	float plane_Ks_R, plane_Ks_G, plane_Ks_B;

	printf("Input file: %s \n", filename);

	fopen_s(&f1, filename, "rb");

	for (int i = 0; i < 5; i++)
	{
		rd = fread(type, 1, 5, f1); //read type

		if (strcmp(type, SCENE) == 0 ){
			//scene 0,0,-2,0,1,0,10,8,2,512,512,0.5,0.2,0,0.0,0.5,0.5
			printf("\nscene");

			fscanf_s(f1, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\r\n", 
				&Px, &Py, &Pz, &UPx, &UPy, &UPz, &width_x, &width_y, &width_z, &screen_x, &screen_y,
				&ambient_light_a, &ambient_light_b, &ambient_light_c, &ambient_light_d, &ambient_light_e, &ambient_light_f);

			printf("\n\tCenter:\t(%d,%d,%d) \n\tUp:\t(%d,%d,%d) \n\tWidth:\t(%d,%d,%d) \n\tScreen:\t%dx%d \n\tambient Light:\t(%.1f,%.1f,%.1f,%.1f,%.1f,%.1f)\n", 
				Px, Py, Pz, UPx, UPy, UPz, width_x, width_y, width_z, screen_x, screen_y,
				ambient_light_a, ambient_light_b, ambient_light_c, ambient_light_d, ambient_light_e, ambient_light_f);
		}
		else if (strcmp(type, LIGHT) == 0){
			//light 1,1,1,0.3,0.2,0.6
			//OR if spotlight:
			//light 1,-1,1,0.9,0.1,0.6,0,4,-5.5,30

			printf("\nlight");

			fscanf_s(f1, "%f,%f,%f,%f,%f,%f",&light_dir_x, &light_dir_y, &light_dir_z, &light_intensity_R, &light_intensity_G, &light_intensity_B);

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
			//spher -1,0,-9,1,0.5,0.5,0.5,0,1,1,0,1,1,20
			printf("\nspher");

			fscanf_s(f1, "%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d\r\n", 
				&spher_x, &spher_y, &spher_z, &spher_radius, &Ka_R, &Ka_G, &Ka_B, &Kd_R, &Kd_G, &Kd_B, &Ks_R, &Ks_G, &Ks_B, &shininess);

			printf("\n\tCenter:\t(%d,%d,%d) \n\tRadius:\t(%.1f) \n\tKa:\t(%.1f,%.1f,%.1f) \n\tKd:\t(%.1f,%.1f,%.1f) \n\tKs:\t(%.1f,%.1f,%.1f) \n\tShininess:\t%d \n",
				spher_x, spher_y, spher_z, spher_radius, Ka_R, Ka_G, Ka_B, Kd_R, Kd_G, Kd_B, Ks_R, Ks_G, Ks_B, shininess);

		}
		else if (strcmp(type, PLANE) == 0){
			printf("\nplane");

			fscanf_s(f1, "%f,%f,%f,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n",
				&plane_normal_x, &plane_normal_y, &plane_normal_z, &plane_center_x, &plane_center_y, &plane_center_z, &plane_width, &plane_height,
				&plane_Ka_R, &plane_Ka_G, &plane_Ka_B, &plane_Kd_R, &plane_Kd_G, &plane_Kd_B, &plane_Ks_R, &plane_Ks_G, &plane_Ks_B);

			printf("\n\tNormal:\t(%.1f,%.1f,%.1f) \n\tCenter:\t(%d,%d,%d) \n\tWidth:\t%d \n\tHeight:\t%d \n\tKa:\t(%.1f,%.1f,%.1f) \n\tKd:\t(%.1f,%.1f,%.1f) \n\tKs:\t(%.1f,%.1f,%.1f)\n",
				plane_normal_x, plane_normal_y, plane_normal_z, plane_center_x, plane_center_y, plane_center_z, plane_width, plane_height,
				plane_Ka_R, plane_Ka_G, plane_Ka_B, plane_Kd_R, plane_Kd_G, plane_Kd_B, plane_Ks_R, plane_Ks_G, plane_Ks_B);

		}
		else{
			printf("Error: I can't recognize this: %s \n Exiting...", type);
			exit(1);
		}
	}

	fclose(f1);

}

int main(int  argc, char** argv)
{
	if (argc < 2){
		printf("Please specify a filename. \n Exiting..");
		getc(stdin);
		exit(1);
	}
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowSize(512, 512);
	//glutCreateWindow("Assignment2");

	init(argv[1]);
	

	printf("Program ended, press Enter to exit.");
	getc(stdin);

	////glutDisplayFunc(mydisplay);
	//glutMainLoop();

	////delete[] newPics;
}