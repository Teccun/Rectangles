#pragma once
#include "rectangle.h"

struct event {
	int x, type;
};


bool compareEvents(const event& a, const event& b);

int  scanline(std::vector<rectangle> segments);
std::vector<rectangle> generateRectangles(int numRectangles, float minX, float maxX, float minY, float maxY);


std::vector<rectangle> generateRectangles(int numRectangles, float minX, float maxX, float minY, float maxY);
double generateRandom(double min, double max);

