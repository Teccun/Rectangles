#pragma once
#include "../rectangle.h"


class RectangleIntersectionAlgorithm {
protected:
	rectangle* rectangles_arr;
	std::vector<rectangle> rectangles;
	int numRect;
	unsigned long long k;

	unsigned long long stdoper = 0;

public:
	RectangleIntersectionAlgorithm(std::vector<rectangle> r, unsigned long long& k) { 
		rectangles = r;	this->k = k;
		rectangles_arr = new rectangle[rectangles.size()];
		for (int i = 0; i < rectangles.size(); i++) {
			rectangles_arr[i] = rectangles[i];
		}
		numRect = rectangles.size();
	}
	
	~RectangleIntersectionAlgorithm() { rectangles.clear(); delete[] rectangles_arr; }



	//Метод выполнения вычисления
	virtual void execute() = 0;

};