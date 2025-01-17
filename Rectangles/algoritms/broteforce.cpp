#include "broteforce.h"

void broteforce::execute() {
	int numRect = rectangles.size();

	event* events_arr = fillEvents(numRect * 2);
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
			activeYStart.addNewY(newYStart, 1);
			activeYStart.addNewY(newYEnd, -1);
			activeYEnd.addNewY(newYStart, 1);
			activeYEnd.addNewY(newYEnd, -1);
		}
		else {
			activeYStart.deleteY(newYStart);
			activeYStart.deleteY(newYEnd);
			activeYEnd.deleteY(newYStart);
			activeYEnd.deleteY(newYEnd);
		}

		if (i + 1 < numRect * 2 && events_arr[i].x != events_arr[i + 1].x) {
			float x1 = events_arr[i].x;
			float x2 = events_arr[i + 1].x;
			if (x1 == x2)
				continue;

			node* itStart = activeYStart.first;
			node* itEnd = activeYEnd.first->next;

			int countYLines = 0;
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
							}

							if (!isDuplicate) {
								result[countResultRect] = newRect;
								countResultRect++;
							}
						}
					}
				itStart = itStart->next;
				itEnd = itEnd->next;
			}
		}

	}
	
	for (int i = 0; i < countResultRect; i++) {
		std::cout << result[i] << "\n";
	}

	delete[] result;
	delete[] events_arr;
}

broteforce::event* broteforce::fillEvents(const int& size) {
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
	return ev_arr;
}

void broteforce::sortEvents(event * arr, const int& size) {
	std::sort(arr, arr + size);

}

void broteforce::list::addNewY(float& val, int type) {
	node* newNode = new node(val, type);

	if (first == nullptr || first->y >= val) {
		newNode->next = first;
		first = newNode;
	}
	else {
		node* current = first;
		while (current->next != nullptr && current->next->y < val)
			current = current->next;
		newNode->next = current->next;
		current->next = newNode;
	}
}

void broteforce::list::deleteY(float& val) {
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
	while (current->next != nullptr && current->next->y != val)
		current = current->next;
	if (current->next == nullptr)
		return;
	node* tmp = current->next;
	current->next = tmp->next;
	delete tmp;
}