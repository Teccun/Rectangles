#include "myalgoritm.h"
#include "workwithfiles/workwithfiles.h"
#include "algoritms/broteforce.h"

// ������������ ���� sf
#include <SFML/Graphics.hpp>



int main()
{
    
    std::vector<rectangle> rect = readFile();

    broteforce alg(rect, 1);
    alg.execute();

    return 0;
}