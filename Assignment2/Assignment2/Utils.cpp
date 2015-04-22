#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

int Utils::width;
int Utils::height;


void Utils::reverseArray(char* arr, int size)
{
	char temp;
	for (int i = 0; i < size / 2; ++i) {
		temp = arr[size - i - 1];
		arr[size - i - 1] = arr[i];
		arr[i] = temp;
	}
}

void Utils::splitString(const string& str, vector<string>& output){
	string tmp = "";

	for (unsigned int i = 0; i<str.length(); i++){
		if (str[i] != ' ' && str[i] != ','){	//delimiters
			tmp = tmp + str[i];
		}
		else{
			if (tmp != "")	output.push_back(tmp);
			tmp = "";
		}
	}
	output.push_back(tmp);
}

int Utils::get1DIndexFrom2D(int x, int y)
{
	return Utils::width*y + x;
}

void Utils::set2DArraySizes(int width, int height)
{
	Utils::width = width;
	Utils::height = height;
}