#include "rectangle.h"

std::ostream& operator << (std::ostream& os, const Coord& coord) {
	return os << "(" << coord.X << ", " << coord.Y << ")";
}

std::istream& operator >> (std::istream& in, Coord& coord) {
	if (in)
		in >> coord.X >> coord.Y;
	return in;
}

unsigned long long rectangle::get_intersection() const {
	return intersection;
}

long long rectangle::getLDInterCount() const {
	return getCordLeftDown().interCount;
}

long long rectangle::getRUInterCount() const {
	return getCordRightUp().interCount;
}

Coord rectangle::getCordLeftDown() const {
	return leftDown;
}

Coord rectangle::getCordRightUp() const {
	return rightUp;
}

void rectangle::incrementLDInterCount() {
	leftDown.interCount++;
}

void rectangle::incrementRUInterCount() {
	rightUp.interCount++;
}

void rectangle::decrementLDInterCount() {
	leftDown.interCount--;
}

void rectangle::decrementRUInterCount() {
	rightUp.interCount--;
}

bool Coord::operator < (const Coord& c) const {
	return X < c.X;
}

bool Coord::operator == (const Coord& c) const {
	return X == c.X && Y == c.Y;
}
//bool Coord::operator != (const Coord& c) const {
//	return X != c.X || Y != c.Y;
//}
//bool Coord::operator > (const Coord& c) const {
//
//}
//bool Coord::operator >= (const Coord& c) const {
//
//}
//bool Coord::operator <= (const Coord& c) const {
//
//}

//Coord rectangle::getCordLeftDown() const {
//	return leftDown;
//}
//
//Coord rectangle::getCordRightUp() const {
//	return rightUp;
//}

std::ostream& operator << (std::ostream& os, const rectangle& rect) {
	return os << "LeftDown: " << rect.leftDown << " RightUp: " << rect.rightUp;
}

std::istream& operator >> (std::istream& in, rectangle& rect) {
	if (in) {
		in >> rect.leftDown >> rect.rightUp;
	}
	return in;
}

bool rectangle::operator < (const rectangle& rect) const {
	return leftDown < rect.leftDown;
}

bool rectangle::operator == (const rectangle& rect) const {
	return leftDown == rect.leftDown && rightUp == rect.rightUp;
}
//bool rectangle::operator != (const rectangle& rect) const {
//
//}
//bool rectangle::operator > (const rectangle& rect) const {
//
//}
//bool rectangle::operator >= (const rectangle& rect) const {
//
//}
//bool rectangle::operator <= (const rectangle& rect) const {
//
//}

bool rectangle::areRectanglesIntersecting(const rectangle& B) {
	return (this->getCordLeftDown().X < B.getCordRightUp().X and
		this->getCordRightUp().X > B.getCordLeftDown().X and
		this->getCordLeftDown().Y < B.getCordRightUp().Y and
		this->getCordRightUp().Y > B.getCordLeftDown().Y);
}

void rectangle::incrInter() {
	intersection++;
}

void rectangle::decInter() {
	intersection--;
}