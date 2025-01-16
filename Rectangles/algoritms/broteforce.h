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
	};

	class list {
	public:
		node* first = nullptr;

		void addNewY(node* other);
		void deleteY(node* other);
	};

public:
	broteforce(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {}

	event* fillEvents(const int &size);
	void sortEvents(event* arr, const int &size);

	void execute();
};

int getPrecision(const float& number);