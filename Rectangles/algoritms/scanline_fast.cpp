#include "scanline_fast.h"

scanline_fast::scanline_fast(std::vector<rectangle>& r, unsigned long long k) : RectangleIntersectionAlgorithm(r, k) {
	sizeEvents = numRect * 2;
	events = new event[sizeEvents];

	for (int i = 0; i < numRect; i++) {
		event newStart;
		newStart.x = rectangles_arr[i].getCordLeftDown().X;
		newStart.type = 1;
		event newEnd;
		newEnd.x = rectangles_arr[i].getCordRightUp().X;
		newEnd.type = -1;
		events[2 * i] = newStart;
		events[2 * i + 1] = newEnd;
	}
}

void scanline_fast::bubbleSort() {
	event tmp;
	for (int i = 0; i < sizeEvents - 1; i++) {
		for (int j = 0; j < sizeEvents - 1; j++) {
			if (events[j].x > events[j + 1].x || (events[j].x == events[j + 1].x && events[j].type > events[j + 1].type)) {
				tmp = events[j];
				events[j] = events[j + 1];
				events[j + 1] = tmp;
				stdoper++;
			}
		}
	}
}

void scanline_fast::execute() {
	auto start = std::chrono::high_resolution_clock::now();
	bubbleSort();

	/*Выигрышь в скорости получается в том, что заранее известры все "события"*/

	list yList;

	/*Хммм... можно избавиться от верхнего создания массива и оставить просто сразу сортировку вставками. Да так будет лучше Плюс - увеличение скорости выполнения алгоритма*/
	for (int i = 0; i < numRect; i++) {

		float y1 = rectangles_arr[i].getCordLeftDown().Y;
		float y2 = rectangles_arr[i].getCordRightUp().Y;

		bool y1Ex = false;
		bool y2Ex = false;

		node* current = yList.first;
		while (current != nullptr) {
			if (current->y == y1)
				y1Ex = true;
			if (current->y == y2)
				y2Ex = true;

			current = current->next;
			stdoper++;
		}

		if (!y1Ex)
			yList.addNewY(y1, 0, stdoper);
		if (!y2Ex)
			yList.addNewY(y2, 0, stdoper);
	}

	node* y1Node = yList.first;
	while (y1Node != nullptr && y1Node->next != nullptr) {
		float y1 = y1Node->y;
		float y2 = y1Node->next->y;

		for (int i = 0; i < sizeEvents - 1; i++) {
			float x1 = events[i].x;
			float x2 = events[i + 1].x;
			if (x1 == x2)
				continue;
			Coord midP = { (x1 + x2) / 2, (y1 + y2) / 2 };

			int coverCount = 0;
			for (int j = 0; j < numRect; j++) {
				if (rectangles_arr[j].containsPoint(midP))
					coverCount++;
				stdoper++;
			}

			if (coverCount >= k) {
				Coord LD = { x1, y1 };
				Coord RU = { x2, y2 };
				rectangle res = { LD, RU };

				if (numRect <= 5)
					std::cout << res << '\n';

			}
			stdoper++;
		}
		y1Node = y1Node->next;
		stdoper++;
	}

	yList.clear();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << stdoper << '\n';
	std::cout << duration.count() << '\n';
	std::cout << float(duration.count()) / float(stdoper) << '\n';
}

void scanline_fast::list::addNewY(float& val, int type, unsigned long long int& count) {
	node* newNode = new node(val, type);

	if (first == nullptr || first->y >= val) {
		newNode->next = first;
		first = newNode;
	}
	else {
		node* current = first;
		while (current->next != nullptr && current->next->y < val) {
			current = current->next;
			count++;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

void scanline_fast::list::deleteY(float& val, unsigned long long int& count) {
	if (first == nullptr) {
		return;
	}

	if (first->y == val) {
		node* tmp = first;
		first = first->next;
		delete tmp;
		return;
	}

	node* current = first;
	while (current->next != nullptr && current->next->y != val) {
		current = current->next;
		count++;
	}
	if (current->next == nullptr)
		return;
	node* tmp = current->next;
	current->next = tmp->next;
	delete tmp;
}

void scanline_fast::list::clear() {
	node* tmp = first;
	while (first != nullptr) {
		first = first->next;
		delete tmp;
		tmp = first;
	}
}
