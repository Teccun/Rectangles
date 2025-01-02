#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <math.h>
#include "rectangle.h"
#include <ctime>
#include <iostream>


struct Coord {
	float X;
	float Y;
	char type;
	long long interCount = 0;

	bool operator < (const Coord& c) const;

	bool operator == (const Coord& c) const;

	/*bool Coord::operator != (const Coord& c) const;
	bool Coord::operator > (const Coord& c) const;
	bool Coord::operator >= (const Coord& c) const;
	bool Coord::operator <= (const Coord& c) const;*/
};
std::ostream& operator << (std::ostream& os, const Coord& coord);
std::istream& operator >> (std::istream& in, Coord& coord);

class rectangle {
private:
	Coord leftDown;
	Coord rightUp;
	unsigned long long intersection = 0;
public:
	rectangle(Coord leftDown = {0, 0}, Coord rightUp = {0, 0}) : leftDown(leftDown), rightUp(rightUp) {
		this->leftDown = leftDown; this->leftDown.type = 1; this->rightUp = rightUp; this->rightUp.type = -1; }
	~rectangle() {}

	unsigned long long get_intersection() const;
	long long getLDInterCount() const;
	long long getRUInterCount() const;
	Coord getCordLeftDown() const;
	Coord getCordRightUp() const;
	void incrementLDInterCount();
	void incrementRUInterCount();
	void decrementLDInterCount();
	void decrementRUInterCount();
	
	void incrInter();
	void decInter();

	bool areRectanglesIntersecting(const rectangle& B);

	friend std::ostream& operator << (std::ostream& os, const rectangle& rect);
	friend std::istream& operator >> (std::istream& in, rectangle& rect);


	bool operator < (const rectangle& rect) const;

	bool operator == (const rectangle& rect) const;

	/*bool operator != (const rectangle& rect) const;
	bool operator > (const rectangle& rect) const;
	bool operator >= (const rectangle& rect) const;
	bool operator <= (const rectangle& rect) const;*/
};
std::ostream& operator << (std::ostream& os, const rectangle& rect);
std::istream& operator >> (std::istream& in, rectangle& rect);