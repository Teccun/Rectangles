#include "interface.h"
#include "locale.h"
#include <crtdbg.h>

int main()
{
    setlocale(LC_ALL, "ru");

    interface ui;
    ui.run();

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}