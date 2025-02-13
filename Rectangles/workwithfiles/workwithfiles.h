#pragma once
#include "../rectangle.h"

std::vector<rectangle> readFile(std::string& namefile);

void writeFile(std::vector<rectangle>& rectangles);