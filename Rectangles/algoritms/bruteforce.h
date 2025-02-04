#pragma once
#include "algoritms.h"

class bruteforce : public RectangleIntersectionAlgorithm {
private:
	struct event {
		float x, y1, y2;
		int type;
	};

	event* events;
	unsigned int sizeEvents = 0;

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
		void clear();
	};

public:
	bruteforce(std::vector<rectangle>& r, unsigned long long k);
	~bruteforce() {
		delete[] events;
	}
	
	void bubbleSort();

	void execute();
};