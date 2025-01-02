#include <iostream>
#include "myalgoritm.h"
#include "workwithfiles/workwithfiles.h"
#include "algoritms/broteforce.h"

using namespace std;

int main()
{
    
    std::vector<rectangle> rect = readFile();

    broteforce alg(rect, 0);
    alg.execute();

}