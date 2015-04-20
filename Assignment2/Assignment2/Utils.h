#pragma once
#include <string>
#include <vector>
using namespace std;


class Utils
{
public:
	Utils();
	~Utils();

	static void reverseArray(char* arr, int size);
	static void splitString(const string& str, vector<string>& output);

};

