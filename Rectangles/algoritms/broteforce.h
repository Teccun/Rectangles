#pragma once
#include "algoritms.h"

class broteforce : public RectangleIntersectionAlgorithm {
public:
	broteforce(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {}

	void execute();
};

int getPrecision(const float& number);