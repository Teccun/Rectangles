#include "interface.h"
#include "locale.h"
#include <crtdbg.h>

/*
void bruteforce::initPoints() {
	int i = 0;
	for (int j = 0; j < numRect; j++) {
		float xLD = rectangles_arr[i].getCordLeftDown().X;
		float yLD = rectangles_arr[i].getCordLeftDown().Y;
		points.addNewPoint(xLD, yLD, 1, &rectangles_arr[i], stdoper);
		i++;

		float xRU = rectangles_arr[i].getCordRightUp().X;
		float yRU = rectangles_arr[i].getCordRightUp().Y;
		points.addNewPoint(xRU, yRU, -1, &rectangles_arr[i], stdoper);
		i++;

		stdoper++;
	}
}

void bruteforce::list::addNewPoint(float& x, float& y, int type, rectangle* rect, unsigned long long int& count) {
	point* newPoint = new point(x, y, type, rect);

	if (first == nullptr || first->X >= x || first->Y >= y) {
		newPoint->next = first;
		first = newPoint;
		count++;
	}
	else {
		point* current = first;
		while (current->next != nullptr && current->next->Y < y && current->next->X < x) {
			current = current->next;
			count++;
		}
		newPoint->next = current->next;
		current->next = newPoint;
	}
}
*/

/*
������ ������ ���� ���. ������ - �����������, � �������. ������� ��������� ������, ������� ��������� ������������ �������
������ - ���� � �������� ���������������� ����������������, ����� ������� ������. �������� ������� ����� ������� � ������� ���������.
����� ������ ��������� ������������. �������� � ��� �����.
�������� ���������
� ������� ���������� ��������
*/

int main()
{
    setlocale(LC_ALL, "ru");

    interface ui;
    ui.run();

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}