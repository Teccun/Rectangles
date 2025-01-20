#pragma once
#include "algoritms.h"

class bruteforce : public RectangleIntersectionAlgorithm {
private:
	struct point {
		float X, Y;
		int type;
		int rectInd;

		bool operator < (const point& other) const {
			return X < other.X || Y < other.Y || type > other.type;
		}
	};
	
	struct activeRect {
		rectangle rect;
		bool active;
	};

	point* points;
	int pointsCount;
	activeRect* actRects;
	int actRectCount = 0;
	int maxActRect;

	void initPoints();
	bool checkInters(rectangle& cur, rectangle& other);
	void findInterArea(activeRect* actRects, int count, rectangle* res, int& resultCount);
	void insertSort(point* arr, int n);


public:
	bruteforce(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {
		pointsCount = numRect * 2;
		points = new point[pointsCount];
		maxActRect = numRect;
		actRects = new activeRect[maxActRect];
		actRectCount = 0;
	}
	~bruteforce() {
		delete[] points;
		delete[] actRects;
	}
	
	void execute();
};