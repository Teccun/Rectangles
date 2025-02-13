#pragma once
#pragma once
#include "algoritms.h"

class scanline_bruteforce : public RectangleIntersectionAlgorithm {
private:
	struct event {
		float x;
		int type;
		rectangle* rect;

		bool operator < (const event& other) const {
			return x < other.x || (x == other.x && type > other.type);
		}
	};

	struct node {
	public:
		float y;
		int type;
		node* next = nullptr;

		node(float& val, int t) : y(val), type(t) {}
	};

	class list {
	public:
		node* first = nullptr;

		void addNewY(float& val, int type, unsigned long long int& count);
		void deleteY(float& val, unsigned long long int& count);
	};

public:
	scanline_bruteforce(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {}

	event* fillEvents(const int& size);
	void sortEvents(event* arr, const int& size);

	void execute();
};