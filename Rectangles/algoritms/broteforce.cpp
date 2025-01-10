#include "broteforce.h"

struct event {
	float x;
	int type;
	rectangle rect;

	bool operator < (const event& other) const {
		return x < other.x || (x == other.x && type > other.type);
		/*if (x != other.x)
			return x < other.x;
		return type < other.type;*/
	}
};

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
	std::vector<event> events;
	for (const auto& rect : rectangles) {
		events.push_back({ rect.getCordLeftDown().X, 1, rect}); // Начало прямоугольника
		events.push_back({ rect.getCordRightUp().X, -1, rect}); // Конец прямоугольника
	}
	std::sort(events.begin(), events.end()); // Сортируем события по X

	// Множество активных прямоугольников (по Y)
	std::multiset<float> activeYStart, activeYEnd;
	std::vector<rectangle> result;

	// Перебираем события
	for (size_t i = 0; i < events.size(); ++i) {
		const event& e = events[i];

		if (e.type == 1) {
			// Начало прямоугольника: добавляем его Y-интервал
			activeYStart.insert(e.rect.getCordLeftDown().Y);
			activeYEnd.insert(e.rect.getCordRightUp().Y);
		}
		else {
			// Конец прямоугольника: удаляем его Y-интервал
			activeYStart.erase(activeYStart.find(e.rect.getCordLeftDown().Y));
			activeYEnd.erase(activeYEnd.find(e.rect.getCordRightUp().Y));
		}

		// Если это не последнее событие и X изменился
		if (i + 1 < events.size() && events[i].x != events[i + 1].x) {
			float x1 = events[i].x;
			float x2 = events[i + 1].x;

			// Перебираем Y-интервалы, где количество покрытий >= k
			auto itStart = activeYStart.begin();
			auto itEnd = activeYEnd.begin();
			float prevY = -INFINITY;

			while (itStart != activeYStart.end() && itEnd != activeYEnd.end()) {
				float y1 = *itStart;
				float y2 = *itEnd;

				// Если количество покрытий >= k, добавляем прямоугольник
				if (std::distance(activeYStart.lower_bound(y1), activeYStart.upper_bound(y2)) >= k) {
					rectangle newRect = { {x1, y1}, {x2, y2} };

					// Проверяем, что новый прямоугольник не содержится в уже добавленных
					bool isDuplicate = false;
					for (const auto& existingRect : result) {
						if (newRect.isInside(existingRect)) {
							isDuplicate = true;
							break;
						}
					}

					if (!isDuplicate) {
						result.push_back(newRect);
					}
				}

				++itStart;
				++itEnd;
			}
		}
	}
	/*std::vector<event> events;
	for (const auto& rect : rectangles) {
		events.push_back({ rect.getCordLeftDown().X, 1, rect });
		events.push_back({ rect.getCordRightUp().X, -1, rect });
	}

	std::sort(events.begin(), events.end());

	std::multiset<float> activeYStart, activeYEnd;
	std::vector<rectangle> result;

	for (int i = 0; i < events.size(); i++) {
		const event& e = events[i];

		if (e.type == 1) {
			activeYStart.insert(e.rect.getCordLeftDown().Y);
			activeYEnd.insert(e.rect.getCordRightUp().Y);
		}
		else {
			activeYStart.erase(activeYStart.find(e.rect.getCordLeftDown().Y));
			activeYEnd.erase(activeYEnd.find(e.rect.getCordRightUp().Y));
		}

		if (i + 1 < events.size() && events[i].x != events[i + 1].x) {
			float x1 = events[i].x;
			float x2 = events[i + 1].x;

			auto itStart = activeYStart.begin();
			auto itEnd = activeYEnd.begin();
			float prevY = -INFINITY;

			while (itStart != activeYStart.end() && itEnd != activeYEnd.end()) {
				float y1 = *itStart;
				float y2 = *itEnd;

				// Если количество покрытий >= k, добавляем прямоугольник
				if (std::distance(activeYStart.lower_bound(y1), activeYStart.upper_bound(y2)) >= k) {
					rectangle new_rect = { {x1, y1}, {x2, y2} };
					bool isDupl = false;
					for (const auto& rect : result) {
						if (new_rect.isInside(rect)) {
							isDupl = true;
							break;
						}
					}
					if (!isDupl)
						result.push_back(new_rect);
				}

				++itStart;
				++itEnd;
			}
		}
	}*/
	
	std::vector<rectangle> finalRes;
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
	}
}

