#pragma once
#include "algoritms/bruteforce.h"
#include "algoritms/scanline.h"
enum class AlgType {
	BRUTEFORCE,
	SCANLINE
};

double generateRandom(float min, float max);
std::vector<rectangle> generateRectangles(unsigned long long int numRectangles, float minX, float maxX, float minY, float maxY);

class Test {
private:

	void testCase1(AlgType type);
	void testCase2(AlgType type);
	void testCase3(AlgType type);
	void testCase4(AlgType type);
	void testCase5(AlgType type);
	void testCase6(AlgType type);

	void runSingleTest(std::vector<rectangle>& rect, const std::string& testName, AlgType type);

public:
	void runTests(AlgType type);
	void generateTest(AlgType type, std::vector<rectangle>& rect);
};