#pragma once
#include "../rectangle.h"


class RectangleIntersectionAlgorithm {
protected:
	std::vector<rectangle> rectangles;
	unsigned long long k;

public:
	RectangleIntersectionAlgorithm(std::vector<rectangle>& r, unsigned long long& k) { rectangles = r;	this->k = k; }

	//����� ���������� ����������
	virtual void execute() = 0;

};