#pragma once
#include "../rectangle.h"


class RectangleIntersectionAlgorithm {
protected:
	rectangle* rectangles_arr;
	std::vector<rectangle> rectangles;
	unsigned long long k;

public:
	RectangleIntersectionAlgorithm(std::vector<rectangle>& r, unsigned long long& k) { 
		rectangles = r;	this->k = k;
		rectangles_arr = new rectangle[rectangles.size()];
		for (int i = 0; i < rectangles.size(); i++) {
			rectangles_arr[i] = rectangles[i];
		}
	}
	
	~RectangleIntersectionAlgorithm() { rectangles.clear(); delete[] rectangles_arr; }



	//Метод выполнения вычисления
	virtual void execute() = 0;

};