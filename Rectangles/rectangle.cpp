#include "rectangle.h"

std::ostream& operator << (std::ostream& os, const Coord& coord) {
	return os << "(" << coord.X << ", " << coord.Y << ")";
}

std::istream& operator >> (std::istream& in, Coord& coord) {
	if (in)
		in >> coord.X >> coord.Y;
	return in;
}

Coord rectangle::getCordLeftDown() const {
	return leftDown;
}

Coord rectangle::getCordRightUp() const {
	return rightUp;
}

bool Coord::operator < (const Coord& c) const {
	return X < c.X;
}

bool Coord::operator == (const Coord& c) const {
	return X == c.X && Y == c.Y;
}

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

bool rectangle::containsPoint(const Coord& p) {
	return (p.X <= rightUp.X && p.X >= leftDown.X &&
		p.Y >= leftDown.Y && p.Y <= rightUp.Y);
}

bool rectangle::areRectanglesIntersecting(const rectangle& B) {
	return (this->getCordLeftDown().X < B.getCordRightUp().X and
		this->getCordRightUp().X > B.getCordLeftDown().X and
		this->getCordLeftDown().Y < B.getCordRightUp().Y and
		this->getCordRightUp().Y > B.getCordLeftDown().Y);
}

bool rectangle::isInside(const rectangle& r) {
	return (this->getCordLeftDown().X >= r.getCordLeftDown().X &&
		this->getCordLeftDown().Y >= r.getCordLeftDown().Y &&
		this->getCordRightUp().X <= r.getCordRightUp().X &&
		this->getCordRightUp().Y <= r.getCordRightUp().Y);
}