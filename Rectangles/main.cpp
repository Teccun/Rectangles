//#include "myalgoritm.h"
//#include "workwithfiles/workwithfiles.h"
//#include "algoritms/broteforce.h"
#include "interface.h"

#include "locale.h"
// ������������ ���� sf
#include <SFML/Graphics.hpp>

#include <crtdbg.h>

/*
�����:
2) ������� �������� �����. �� ������ ���� �������������� (����� ��� �� �������)
3) ������� ������ �������
4) ������� ���������������� ��������
5) ������� ��������� - ���������� +-
6) ������� ��������� - �����������
7) �h��e���� � ������� ��������� ���������������

Given a plane with N rectangles, find the points covered by at least k of them. The input data consists of the coordinates of the rectangles (lower-left and upper-right corners) and the value of k. The output should be the coordinates of the rectangles formed by the points covered by at least k rectangles
*/

int main()
{
    setlocale(LC_ALL, "ru");

    /*std::vector<rectangle> rect = readFile();
    broteforce alg(rect, 3);
    alg.execute();*/

    interface ui;
    ui.run();


    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}