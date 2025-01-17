#pragma once
#include "algoritms.h"

class broteforce : public RectangleIntersectionAlgorithm {
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

		void addNewY(float& val, int type);
		void deleteY(float& val);
	};

public:
	broteforce(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {}

	event* fillEvents(const int &size);
	void sortEvents(event* arr, const int &size);

	void execute();
};