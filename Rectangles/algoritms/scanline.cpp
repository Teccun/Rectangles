#include "scanline.h"

void scanline::execute() {
	
	auto start = std::chrono::high_resolution_clock::now();

	if (numRect == 0)
		return;
	event* events_arr = fillEvents(numRect * 2);
	sortEvents(events_arr, numRect * 2);

	list activeYStart, activeYEnd;
	rectangle* result = new rectangle[(numRect * 2) * (numRect * 2)]; // чтобы уж наверняка.
	int countResultRect = 0;
	stdoper += 2;

	for (int i = 0; i < numRect * 2; i++) {
		const event& e = events_arr[i];

		float newYStart, newYEnd;
		newYStart = e.rect->getCordLeftDown().Y;
		newYEnd = e.rect->getCordRightUp().Y;
		stdoper += 4;

		if (e.type == 1) {
			activeYStart.addNewY(newYStart, 1, stdoper);
			activeYStart.addNewY(newYEnd, -1, stdoper);
			activeYEnd.addNewY(newYStart, 1, stdoper);
			activeYEnd.addNewY(newYEnd, -1, stdoper);
		}
		else {
			activeYStart.deleteY(newYStart, stdoper);
			activeYStart.deleteY(newYEnd, stdoper);
			activeYEnd.deleteY(newYStart, stdoper);
			activeYEnd.deleteY(newYEnd, stdoper);
		}

		if (i + 1 < numRect * 2 && events_arr[i].x != events_arr[i + 1].x) {
			float x1 = events_arr[i].x;
			float x2 = events_arr[i + 1].x;
			stdoper += 2;
			if (x1 == x2)
				continue;

			node* itStart = activeYStart.first;
			node* itEnd = activeYEnd.first->next;

			int countYLines = 0;
			while (itEnd != nullptr) {
				float y1 = itStart->y;
				float y2 = itEnd->y;
				stdoper += 2;

				if (itStart->type == 1)
					countYLines++;
				else
					countYLines--;
				stdoper += 1;

				if (countYLines >= k) {
					rectangle newRect = { {x1, y1}, {x2, y2} };
					if (y1 != y2) {
						bool isDuplicate = false;
						for (int j = 0; j < countResultRect; j++) {
							if (newRect.isInside(result[j])) {
								isDuplicate = true;
								stdoper += 4;
								break;
							}
							stdoper++;
						}

						if (!isDuplicate) {
							result[countResultRect] = newRect;
							countResultRect++;
							stdoper++;
						}
					}
					stdoper++;
				}
				itStart = itStart->next;
				itEnd = itEnd->next;
			}
		}

	}

	for (int i = 0; i < countResultRect; i++) {
		std::cout << result[i] << "\n";
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << stdoper << '\n';
	std::cout << duration.count() << '\n';

	std::cout << duration.count() / stdoper << '\n';

	delete[] result;
	delete[] events_arr;
}

scanline::event* scanline::fillEvents(const int& size) {
	event* ev_arr = new event[size * 2];
	for (int i = 0; i < size; i++) {
		event newStartEvent;
		newStartEvent.x = rectangles_arr[i].getCordLeftDown().X;
		newStartEvent.type = 1;
		newStartEvent.rect = &rectangles_arr[i];
		event newEndEvent;
		newEndEvent.x = rectangles_arr[i].getCordRightUp().X;
		newEndEvent.type = -1;
		newEndEvent.rect = &rectangles_arr[i];
		ev_arr[i * 2] = newStartEvent;
		ev_arr[i * 2 + 1] = newEndEvent;
	}
	stdoper += 8 * size;
	return ev_arr;
}

void scanline::sortEvents(event* arr, const int& size) {
	std::sort(arr, arr + size);
	stdoper += (size * std::log2(size));

}

void scanline::list::addNewY(float& val, int type, unsigned long long int& count) {
	node* newNode = new node(val, type);

	if (first == nullptr || first->y >= val) {
		newNode->next = first;
		first = newNode;
		count++;
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

void scanline::list::deleteY(float& val, unsigned long long int& count) {
	if (first == nullptr) {
		return;
	}

	if (first->y == val) {
		node* tmp = first;
		first = first->next;
		delete tmp;
		count++;
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
	count++;
	delete tmp;
}