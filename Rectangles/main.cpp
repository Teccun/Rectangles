#include "interface.h"
#include "locale.h"
#include <crtdbg.h>

int main()
{
    setlocale(LC_ALL, "ru");

    /*interface ui;
    ui.run();*/

    std::vector<rectangle> rect = {
        {{-1.5, 0.5}, {2, 1.5}},
        {{-0.5, 0}, {0, 2.25}},
        {{0, 0}, {1.5, 2.25}},
        {{1, 2}, {4, 3}}
    };

    native al(rect, 1);
    al.execute();

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}