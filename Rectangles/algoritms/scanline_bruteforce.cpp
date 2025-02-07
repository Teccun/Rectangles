#include "scanline_bruteforce.h"

void scanline_bruteforce::execute() {

	auto start = std::chrono::high_resolution_clock::now();

	if (numRect == 0)
		return;
	event* events_arr = fillEvents(numRect);
	sortEvents(events_arr, numRect * 2);

	list activeYStart, activeYEnd;
	rectangle* result = new rectangle[(numRect * 2) * (numRect * 2)]; // чтобы уж наверняка.
	int countResultRect = 0;

	for (int i = 0; i < numRect * 2; i++) {
		const event& e = events_arr[i];

		float newYStart, newYEnd;
		newYStart = e.rect->getCordLeftDown().Y;
		newYEnd = e.rect->getCordRightUp().Y;

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

		if (i + 1 < numRect * 2 && events_arr[i].x != events_arr[i + 1].x && activeYEnd.first != nullptr) {
			float x1 = events_arr[i].x;
			float x2 = events_arr[i + 1].x;

			node* itStart = activeYStart.first;
			node* itEnd = activeYEnd.first->next;

			int countYLines = 0;
			/*Причиина всех моих несчастий. Получается, тут я обхожу всё что у меня скапливается в списке. В худшем случае это все. Внутри ещё полная проверка на повторы идет*/
			while (itEnd != nullptr) {
				float y1 = itStart->y;
				float y2 = itEnd->y;

				if (itStart->type == 1)
					countYLines++;
				else
					countYLines--;

				if (countYLines >= k) {
					rectangle newRect = { {x1, y1}, {x2, y2} };
					if (y1 != y2) {
						bool isDuplicate = false;
						for (int j = 0; j < countResultRect; j++) {
							if (newRect.isInside(result[j])) {
								isDuplicate = true;
								break;
							}
							stdoper++;
						}

						if (!isDuplicate) {
							result[countResultRect] = newRect;
							countResultRect++;
						}
					}
				}
				itStart = itStart->next;
				itEnd = itEnd->next;
				stdoper++;
			}
		}

	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	if (numRect <= 5)
	{
		for (int i = 0; i < countResultRect; i++) {
			std::cout << result[i] << "\n";
		}
	}

	std::cout << stdoper << '\n';
	std::cout << duration.count() << '\n';
	std::cout << float(duration.count()) / float(stdoper) << '\n';

	delete[] result;
	delete[] events_arr;
}

scanline_bruteforce::event* scanline_bruteforce::fillEvents(const int& size) {
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
		stdoper++;
	}
	return ev_arr;
}

void scanline_bruteforce::sortEvents(event* arr, const int& size) {
	std::sort(arr, arr + size);
	stdoper += (size * std::log2(size));
}

void scanline_bruteforce::list::addNewY(float& val, int type, unsigned long long int& count) {
	node* newNode = new node(val, type);

	if (first == nullptr || first->y >= val) {
		newNode->next = first;
		first = newNode;
	}
	else {
		node* current = first;
		while (current->next != nullptr && current->next->y < val) {
			current = current->next;
			//count++;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

void scanline_bruteforce::list::deleteY(float& val, unsigned long long int& count) {
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
		//count++;
	}
	if (current->next == nullptr)
		return;
	node* tmp = current->next;
	current->next = tmp->next;
	delete tmp;
}