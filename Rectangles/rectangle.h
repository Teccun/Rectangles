#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <fstream>   
#include <iostream>  
#include <string>    
#include <iomanip>   // manipulator
#include <sstream>   // string stream
#include <math.h>    
#include <algorithm>
#include <vector>
#include <set>
#include <map>

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
	unsigned long long intersection = 1;
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
	bool isInside(const rectangle& r);

	friend std::ostream& operator << (std::ostream& os, const rectangle& rect);
	friend std::istream& operator >> (std::istream& in, rectangle& rect);


	bool operator < (const rectangle& rect) const;

	bool operator == (const rectangle& rect) const;
};
std::ostream& operator << (std::ostream& os, const rectangle& rect);
std::istream& operator >> (std::istream& in, rectangle& rect);