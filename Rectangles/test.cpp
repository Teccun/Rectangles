#include "test.h"

// ���������� ��������� ����� � �������� ���������
double generateRandom(float min, float max) {
	return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}
// ��������� ��������� ����� ��������������� � �������� ���������� �������.
// ������ �������� - ����� �������������
// ������ - minX, ������ - maxX, ��������� - minY, ����� - maxY.
std::vector<rectangle> generateRectangles(unsigned long long int numRectangles, float minX, float maxX, float minY, float maxY) {

	std::vector<rectangle> rectangles;

	if (minX >= maxX || minY >= maxY) {
		std::cout << "������������ ���� ���������\n";
		return rectangles;
	}

	srand(static_cast<unsigned>(time(0)));

	for (int i = 0; i < numRectangles; i++) {
		float x1 = generateRandom(minX, maxX);
		float y1 = generateRandom(minY, maxY);
		float x2 = generateRandom(x1, maxX);
		float y2 = generateRandom(y1, maxY);

		Coord leftDown;
		leftDown.X = x1;
		leftDown.Y = y1;
		leftDown.type = 1;
		Coord rightUp;
		rightUp.X = x2;
		rightUp.Y = y2;
		rightUp.type = -1;
		rectangles.emplace_back(leftDown, rightUp);
	}

	return rectangles;
}

void Test::generateTest(AlgType type, std::vector<rectangle>& rect) {
	runSingleTest(rect, "Random generation", type);
}

void Test::runSingleTest(std::vector<rectangle>& const rect, const std::string& testName, AlgType type) {
	printf("\n    %s    \n", testName.c_str());
	for (unsigned long long k = 1; k <= rect.size() * 2; k++) {
		printf("\n K = %llu :\n", k);
		switch (type) {
		case AlgType::BRUTEFORCE: {
			scanline_bruteforce alg(rect, k);
			alg.execute();
			break;
		}
		case AlgType::SCANLINE: {
			scanline_fast alg(rect, k);
			alg.execute();
			break;
		}
		}
		printf("\n");
	}
}

void Test::compareTest(AlgType type, std::vector<rectangle>& rect) {
	printf("\n     Compare    \n");
	switch (type) {
	case AlgType::BRUTEFORCE: {
		scanline_bruteforce alg(rect, 1);
		alg.execute();
		break;
	}
	case AlgType::SCANLINE: {
		scanline_fast alg(rect, 1);
		alg.execute();
		break;
	}
	}
	printf("\n");
}

void Test::progressiveTest(AlgType type, std::vector<rectangle>& rect, int& k) {
	printf("\n");
	switch (type) {
	case AlgType::BRUTEFORCE: {
		scanline_bruteforce alg(rect, k);
		alg.execute();
		break;
	}
	case AlgType::SCANLINE: {
		scanline_fast alg(rect, k);
		alg.execute();
		break;
	}
	}
	printf("\n");
}

void Test::testCase1(AlgType type) {
	std::vector<rectangle> rect = {
		{{-1.5, 0.5}, {2, 1.5}},
		{{-0.5, 0}, {0, 2.25}},
		{{0, 0}, {1.5, 2.25}},
		{{1, 2}, {4, 3}}
	};
	runSingleTest(rect, "���� 1", type);
}

void Test::testCase2(AlgType type) {
	std::vector<rectangle> rect = {
		{{-2, -2}, {2, 4}},
		{{-2, -2}, {2, 2}},
		{{-2, -2}, {2, 0}},
		{{-6, -2}, {4, 2}}
	};
	runSingleTest(rect, "���� 2", type);
}

void Test::testCase3(AlgType type) {
	std::vector<rectangle> rect = {
		{{-4, -2}, {4, 2}},
		{{-2, -1}, {2, 1}},
		{{-1, -3}, {1, 3}}
	};
	runSingleTest(rect, "���� 3", type);
}

void Test::testCase4(AlgType type) {
	std::vector<rectangle> rect = {
		{{-4, -2}, {1, 1}},
		{{-1, -4}, {2, -1}},
		{{0, -2}, {3, 3}}
	};
	runSingleTest(rect, "���� 4", type);
}

void Test::testCase5(AlgType type) {
	std::vector<rectangle> rect = {
		{{-3, -3}, {3, 0}},
		{{-1, 0.25}, {1.85, 0.75}},
		{{-3, 1}, {3, 3}}
	};
	runSingleTest(rect, "���� 5", type);
}

void Test::testCase6(AlgType type) {
	std::vector<rectangle> rect = {
		{{0.5, 0.5}, {2, 3}},
		{{1.5, 2}, {3, 4}}
	};
	runSingleTest(rect, "���� 6", type);
}

void Test::testCase7(AlgType type) {
	std::vector<rectangle> rect = {
		{{0, 0}, {2, 3}},
		{{3, 0}, {5, 3}}
	};
	runSingleTest(rect, "���� 7", type);
}

void Test::testCase8(AlgType type) {
	std::vector<rectangle> rect = {
		{{0, 0}, {2, 2}},
		{{3, 1}, {5, 3}}
	};
	runSingleTest(rect, "���� 8", type);
}

void Test::testCase9(AlgType type) {
	std::vector<rectangle> rect = {
		{{0, 0}, {2, 2}},
		{{0, 3}, {2, 5}}
	};
	runSingleTest(rect, "���� 9", type);
}

void  Test::runTests(AlgType type) {
	testCase1(type);
	testCase2(type);
	testCase3(type);
	testCase4(type);
	testCase5(type);
	testCase6(type);
	testCase7(type);
	testCase8(type);
	testCase9(type);
}