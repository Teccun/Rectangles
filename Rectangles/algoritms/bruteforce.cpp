#include "bruteforce.h"

void bruteforce::initPoints() {
	int i = 0;
	for (int j = 0; j < numRect; j++) {
		points[i].X = rectangles_arr[i].getCordLeftDown().X;
		points[i].Y = rectangles_arr[i].getCordLeftDown().Y;
		points[i].type = 1;
		points[i].rectInd = i;
		i++;

		points[i].X = rectangles_arr[i].getCordRightUp().X;
		points[i].Y = rectangles_arr[i].getCordRightUp().Y;
		points[i].type = -1;
		points[i].rectInd = i;
		i++;

		stdoper += 8;
	}
	insertSort(points, pointsCount);
}
bool bruteforce::checkInters(rectangle& cur, rectangle& other) {
	return cur.areRectanglesIntersecting(other);
}
void bruteforce::findInterArea(activeRect* actRects, int count, rectangle* res, int& resultCount) {
	if (count < k)
		return;

	float minX = points[0].X;
	float maxX = points[pointsCount - 1].X;
	float minY = actRects[0].rect.getCordLeftDown().Y;
	float maxY = actRects[0].rect.getCordRightUp().Y;
	stdoper += 4;

	for (int i = 1; i < count; i++) {
		if (!actRects[i].active)
			continue;

		minX = std::max(minX, actRects[i].rect.getCordLeftDown().X);
		maxX = std::min(maxX, actRects[i].rect.getCordRightUp().X);
		minY = std::max(minY, actRects[i].rect.getCordLeftDown().Y);
		maxY = std::min(maxY, actRects[i].rect.getCordRightUp().Y);
		stdoper += 4;
	}
	if (minX <= maxX && minY <= maxY) {
		rectangle newRect = { {minX, minY}, {maxX, maxY} };
		res[resultCount] = newRect;
		resultCount++;
	}
}


void bruteforce::insertSort(point* arr, int num) {
	for (int i = 1; i < num; i++) {
		point key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] < key) {
			arr[j + 1] = arr[j];
			j--;
			stdoper++;
		}
		arr[j + 1] = key;
		stdoper++;
	}
}

void bruteforce::execute() {
    auto start = std::chrono::high_resolution_clock::now();

    if (numRect == 0) return;

    initPoints();
    actRectCount = 0;

    rectangle* resultRectangles = new rectangle[numRect * numRect];
    int resultCount = 0;

    float currentX = points[0].X;

    for (int i = 0; i < pointsCount; i++) {
        const point& point = points[i];

        if (point.X != currentX) {
            // Process current slice
            findInterArea(actRects, actRectCount, resultRectangles, resultCount);
            currentX = point.X;
        }

        if (point.type == 1) {
            actRects[actRectCount].rect = rectangles_arr[point.rectInd];
            actRects[actRectCount].active = true;
            actRectCount++;
			stdoper += 3;
        }
        else {
            for (int j = 0; j < actRectCount; j++) {
                if (actRects[j].rect == rectangles_arr[point.rectInd]) {
                    for (int k = j; k < actRectCount - 1; k++) {
                        actRects[k] = actRects[k + 1];
						stdoper++;
					}
                    actRectCount--;
					stdoper++;
                    break;
                }
            }
        }
        stdoper++;
    }

    for (int i = 0; i < resultCount; i++) {
        std::cout << resultRectangles[i] << "\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << stdoper << '\n';
    std::cout << duration.count() << '\n';
    std::cout << duration.count() / stdoper << '\n';

    delete[] resultRectangles;

}
