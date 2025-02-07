#pragma once
#pragma once
#include "algoritms.h"

class native : public RectangleIntersectionAlgorithm {
private:

public:
	native(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {}

	void execute();
};