#include "workwithfiles.h"

std::vector<rectangle> readFile() {

	std::ifstream in("in.txt");
	if (!in)
		std::cout << "The file cannot be opened";

	std::vector<rectangle> rectangles;
	rectangle rect;

	while (in >> rect)
		rectangles.push_back(rect);

	in.close();

	return rectangles;
}

void writeFile(std::vector<rectangle>& rectangles) {
	std::ofstream out;
	out.open("out.txt");
	if (!out)
		std::cout << "The file cannot be opened";

	for (size_t i = 0; i < rectangles.size(); i++) {
		out << rectangles[i] << "\n";
	}

	out.close();
}