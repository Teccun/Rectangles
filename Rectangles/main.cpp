//#include "myalgoritm.h"
//#include "workwithfiles/workwithfiles.h"
//#include "algoritms/broteforce.h"
#include "interface.h"

#include "locale.h"
// пространство имен sf
#include <SFML/Graphics.hpp>

#include <crtdbg.h>

/*
Таски:
2) сделать тестовый класс. Он должен быть автоматическим (чтобы это не значило)
3) сделать замеры времени
4) сделать оптимизированный алгоритм
5) сделать интерфейс - консольный +-
6) сделать интерфейс - графический
7) пhодeмать и сделать отрисовку прямоугольников

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