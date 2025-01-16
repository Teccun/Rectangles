#include "broteforce.h"

int getPrecision(const float& number) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(15) << number;
	std::string numStr = oss.str();

	size_t dotPos = numStr.find('.');
	if (dotPos == std::string::npos) {
		return 0;
	}

	size_t lastNonZero = numStr.find_last_not_of('0');
	return lastNonZero - dotPos;
}

bool isPointCovered(const rectangle& rect, float x, float y, float epsilon = 1) {
	return (x >= rect.getCordLeftDown().X && x <= rect.getCordRightUp().X + epsilon &&
		y >= rect.getCordLeftDown().Y && y <= rect.getCordRightUp().Y + epsilon);
}

void broteforce::execute() {
	int numRect = rectangles.size();

	event* events_arr = fillEvents(numRect * 2);
	sortEvents(events_arr, numRect);

	for (int i = 0; i < numRect * 2; i++)
		std::cout << events_arr[i].x << '\n';

	list activeYStart, activeYEnd;
	rectangle* reseult = new rectangle[(numRect * 2) * (numRect * 2)]; // ����� �� ���������.
	int countResultRect = 0;

	for (int i = 0; i < numRect * 2; i++) {
		const event& e = events_arr[i];
		
		node newYStart, newYEnd;
		newYStart.y = e.rect->getCordLeftDown().Y;
		newYStart.type = 1;
		newYEnd.y = e.rect->getCordRightUp().Y;
		newYEnd.type = -1;

		if (e.type == 1) {
			activeYStart.addNewY(&newYStart);
			activeYStart.addNewY(&newYEnd);
			activeYEnd.addNewY(&newYStart);
			activeYEnd.addNewY(&newYEnd);
		}
		else {
			activeYStart.deleteY(&newYStart);
			activeYEnd.deleteY(&newYEnd);
			activeYStart.deleteY(&newYStart);
			activeYEnd.deleteY(&newYEnd);
		}

		if (i + 1 < numRect * 2 && events_arr[i].x != events_arr[i + 1].x) {
			float x1 = events_arr[i].x;
			float x2 = events_arr[i + 1].x;

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
					
					bool isDuplicate = false;
					for (int j = 0; j < countResultRect; j++) {
						if (newRect.isInside(reseult[j])) {
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate) {
						reseult[countResultRect] = newRect;
						countResultRect++;
					}

				}

				itStart = itStart->next;
				itEnd = itEnd->next;
			}
		}

	}
	
	for (int i = 0; i < countResultRect; i++) {
		std::cout << reseult[i] << "\n";
	}
	/*std::vector<rectangle> finalRes;
	for (auto& rect : result) {
		int count = 0;
		for (const auto& r : rectangles) {
			if (rect.isInside(r))
				count++;
		}
		if (count >= k)
			finalRes.push_back(rect);
	}

	for (auto rect : finalRes) {
		std::cout << rect << '\n';
	}*/

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

void broteforce::list::addNewY(node* other) {
	if (first == nullptr) {
		first = other;
	}
	else {
		node* now = first;
		while (now->y > other->y && now->next != nullptr) {
			now = now->next;
		}
		if (now->next == nullptr)
			now->next = other;
		else if (now->next != nullptr && now->next->y != other->y) {
			node* tmp = now->next;
			now->next = other;
			other->next = tmp;
		}
		//�������� now? ��� �� �� �� ����� ���� ����� �� �����
	}
	return;
}

void broteforce::list::deleteY(node* other) {
	node* now = first;
	if (first->next != nullptr) {
		while (now->y != other->y) {
			now = now->next;
		}
		node* tmp = now->next;
		now->next = tmp->next;
		delete tmp;
	}
	else
		delete now;
}