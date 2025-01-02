#pragma once
#include "algoritms/algoritms.h"
#include "rectangle.h"

using namespace std;

class interface {
protected:
	vector<rectangle> setOfRectangles;
 
public:
	interface(vector<rectangle> rect) : setOfRectangles(rect) {}

	void introduction();
};