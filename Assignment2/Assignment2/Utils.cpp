#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

void Utils::reverseArray(char* arr, int size)
{
	char temp;
	for (int i = 0; i < size / 2; ++i) {
		temp = arr[size - i - 1];
		arr[size - i - 1] = arr[i];
		arr[i] = temp;
	}
}