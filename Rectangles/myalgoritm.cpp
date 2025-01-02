#include "myalgoritm.h"
//Пока не трогать. Нужно сделать полный обход, а потом уже приниматься за оптимизацию. Так и сделаем.
bool compareEvents(const event& a, const event& b) {
	return (a.x < b.x || (a.x == b.x && a.type > b.type));
}
int  scanline(std::vector<rectangle> segments) {
	std::vector<event> events;

	for (int i = 0; i < segments.size(); i++) {
		event new_event;
		Coord cld = segments[i].getCordLeftDown();
		Coord cru = segments[i].getCordRightUp();
		new_event.x = cld.X;
		new_event.type = cld.type;
		events.push_back(new_event);
		new_event.x = cru.X;
		new_event.type = cru.type;
		events.push_back(new_event);
	}

	sort(events.begin(), events.end(), compareEvents);

	int cnt = 0, res = 0;

	for (int i = 0; i < events.size(); i++) {
		cnt += events[i].type;
		res = std::max(res, cnt);
	}

	return res;
}

// Генерирует радномное число в заданном диапазоне
double generateRandom(double min, double max) {
	return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}
// Генерация заданного числа прямоугольников в заданной допустимой области.
// Первый аргумент - число треугольников
// Второй - minX, третий - maxX, четвертый - minY, пятый - maxY.
std::vector<rectangle> generateRectangles(int numRectangles, float minX, float maxX, float minY, float maxY) {
	std::vector<rectangle> rectangles;
	srand(static_cast<unsigned>(time(0)));

	for (int i = 0; i < numRectangles; i++) {
		float x1 = generateRandom(minX, maxX);
		float y1 = generateRandom(minY, maxY);
		float x2 = generateRandom(x1, maxX);
		float y2 = generateRandom(y1, maxY);

		Coord leftDown;
		leftDown.X = x1;
		leftDown.Y = y1;
		leftDown.type = 1;
		Coord rightUp;
		rightUp.X = x2;
		rightUp.Y = y2;
		rightUp.type = -1;
		rectangles.emplace_back(leftDown, rightUp);
	}

	return rectangles;
}

