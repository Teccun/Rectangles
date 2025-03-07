#include "interface.h"

/* Text data (menus and other information) */
void interface::displayMenu() {
	clearScreen();
	printf("=== Main menu ===\n");
	printf("1. Problem condition\n");
	printf("2. Scanline Bruteforce\n");
	printf("3. Scanline fast\n");
	printf("4. Algorithm comparison\n");
	printf("5. Algorithm base comparison\n");
	printf("6. Algorithm progressive comparison\n");
	printf("7. Exit\n\n");
}
void interface::problemConditionUI() {
	clearScreen();
	printf("=== ������� ������ ===\n");
	printf("��������������\n");
	printf("�� ��������� ������ N ���������������. ����� �����, �������� �� ����� ��� k �� ���.\n");
	printf("������� ������ � ���������� ��������������� ( ����� ������ � ������ ������� ����) � k.\n");
	printf("����� � ���������� ���������������, ������������ �������, ��������� �� ����� ��� k ����������������.\n");
	waitForKeyPress();
}
void interface::broteforceUI() {
	clearScreen();
	printf("=== Scanline Brute-force method menu ===\n");
	printf("1. Read rectangles from file\n");
	printf("2. Use standart tests\n");
	printf("3. Generate random rectangles for test\n");
	printf("4. Return to Main menu\n\n");
}
void interface::scanlineUI() {
	clearScreen();
	printf("=== Scanline fast method menu ===\n");
	printf("1. Read rectangles from file\n");
	printf("2. Use standart tests\n");
	printf("3. Generate random rectangles for test\n");
	printf("4. Return to Main menu\n\n");
}

/* Catching the user's choice */
int interface::getUserChoice() {
	int choice = 0;
	std::cout << "Enter: ";

	if (!(std::cin >> choice)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
		return -1;
	}

	return choice;
}

/* Handling user selection */
void interface::handleChoiceMainMenu(int choice) {
	switch (choice) {
	case 1:
		problemConditionUI();
		break;
	case 2:
		currentMenu = Menu::BRUTEFORCE;
		break;
	case 3:
		currentMenu = Menu::SCANLINE;
		break;
	case 4:
		algorithmComparison();
		break;
	case 5:
		algorithmBaseComparison();
		break;
	case 6:
		algorithmProgressivComparison();
		break;
	case 7:
		exit();
		break;
	default:
		printf("�������� �����. ���������� �����.\n");
		waitForKeyPress();
		break;
	}
}
void interface::handleChoiceBruteforceMenu(int choice) {
	switch (choice) {
	case 1:
		broteforceReadFromFile();
		break;
	case 2:
		broteforceTestClass();
		break;
	case 3:
		broteforceGenerate();
		break;
	case 4:
		currentMenu = Menu::MAIN;
		break;
	default:
		std::cout << "�������� �����. ���������� �����.\n";
		waitForKeyPress();
		break;
	}
}
void interface::handleChoiceScanlineMenu(int choice) {
	switch (choice) {
	case 1:
		scanlineReadFromFile();
		break;
	case 2:
		scanlineTestClass();
		break;
	case 3:
		scanlineGenerate();
		break;
	case 4:
		currentMenu = Menu::MAIN;
		break;
	default:
		std::cout << "�������� �����. ���������� �����.\n";
		waitForKeyPress();
		break;
	}
}

/* Reading data from .txt file */
void interface::broteforceReadFromFile() {
	clearScreen();
	printf("=== Read from file ===\n");
	printf("������� ���� � ����������� .txt, � ������� �������� ����������\n");
	printf("(������� ���������� ������ ���������: x1 y1 x2 y2 - ����� � ��������� ������)\n"); std::string namefile;
	std::cin >> namefile;

	std::vector<rectangle> rect = readFile(namefile);
	std::cout << "\n������� �������� k: ";

	int k;
	std::cin >> k;
	scanline_bruteforce alg(rect, k);
	alg.execute();
	waitForKeyPress();
}
/* Program operation on standard tests */
void interface::broteforceTestClass() {
	clearScreen();
	Test tests;
	tests.runTests(AlgType::BRUTEFORCE);
	waitForKeyPress();
}
/* Running the program on a randomly generated set of N rectangles in a given area. */
void interface::broteforceGenerate() {
	clearScreen();
	printf("=== Scanline Brote-force with random rectangles ===\n");
	printf("����� (�����) ����� ��������������� � ������� (minX, maxX, minY, maxY ��� float) ��� ��������� ���������\n");
	float minX, maxX, minY, maxY;
	unsigned long long int N;
	std::cin >> N >> minX >> maxX >> minY >> maxY;
	std::vector<rectangle> rect = generateRectangles(N, minX, maxX, minY, maxY);
	Test tests;
	tests.generateTest(AlgType::BRUTEFORCE, rect);
	waitForKeyPress();
}

void interface::scanlineReadFromFile() {
	clearScreen();
	printf("=== Read from file ===\n");
	printf("������� ���� � ����������� .txt, � ������� �������� ����������\n");
	printf("(������� ���������� ������ ���������: x1 y1 x2 y2 - ����� � ��������� ������)\n"); std::string namefile;
	std::cin >> namefile;

	std::vector<rectangle> rect = readFile(namefile);
	std::cout << "\n������� �������� k: ";

	int k;
	std::cin >> k;
	scanline_fast alg(rect, k);
	alg.execute();
	waitForKeyPress();
}
void interface::scanlineTestClass() {
	clearScreen();
	Test tests;
	tests.runTests(AlgType::SCANLINE);
	waitForKeyPress();
}
void interface::scanlineGenerate() {
	clearScreen();
	printf("=== Scanline fast with random rectangles ===\n");
	printf("����� (�����) ����� ��������������� � ������� (minX, maxX, minY, maxY ��� float) ��� ��������� ���������\n");
	float minX, maxX, minY, maxY;
	unsigned long long int N;
	std::cin >> N >> minX >> maxX >> minY >> maxY;
	std::vector<rectangle> rect = generateRectangles(N, minX, maxX, minY, maxY);
	Test tests;
	tests.generateTest(AlgType::SCANLINE, rect);
	waitForKeyPress();
}

void interface::algorithmComparison() {
	clearScreen();
	printf("=== Algorithm comparison ===\n");
	printf("����� (�����) ����� ��������������� � ������� (minX, maxX, minY, maxY ��� float) ��� ��������� ���������\n");
	float minX, maxX, minY, maxY;
	unsigned long long int N;
	std::cin >> N >> minX >> maxX >> minY >> maxY;
	std::vector<rectangle> rect = generateRectangles(N, minX, maxX, minY, maxY);
	Test tests;
	printf("\n=======================================\n");
	tests.generateTest(AlgType::BRUTEFORCE, rect);
	printf("\n=======================================\n");
	tests.generateTest(AlgType::SCANLINE, rect);
	printf("\n=======================================\n");
	waitForKeyPress();
}
void interface::algorithmBaseComparison() {
	clearScreen();
	for (int i = 100; i <= 200; i += 100) {
		std::vector<rectangle> rect = generateRectangles(i, 0, 50, 0, 50);
		Test tests;
		printf("\n=== N - %d ===\n", i);
		printf("=scanline_bruteforce=\n");
		tests.compareTest(AlgType::BRUTEFORCE, rect);
		printf("=scanine fast=\n");
		tests.compareTest(AlgType::SCANLINE, rect);
		printf("=======================================\n");
		rect.clear();
	}
	waitForKeyPress();
}
void interface::algorithmProgressivComparison() {
	clearScreen();
	int count = 5;
	std::vector<rectangle> rect;
	for (int i = 1; i <= 5; i++) {
		Coord ld = { 0, 0 };
		Coord ru = { i, i };
		rectangle newRect = { ld, ru };
		rect.push_back(newRect);
	}
	for (int i = 10; i <= 5000; i += 10) {
		Coord ld = { 0, 0 };
		Coord ru = { i, i };
		rectangle newRect = { ld, ru };
		rect.push_back(newRect);
		count++;
		Test tests;
		for (int k = 1; k < count; k++) {
			printf("\n=== N - %d K - %d===\n", i, k);
			printf("=scanline_bruteforce=\n");
			tests.progressiveTest(AlgType::BRUTEFORCE, rect, k);
			printf("=scanine fast=\n");
			tests.progressiveTest(AlgType::SCANLINE, rect, k);
			printf("=======================================\n");
		}
		printf("\n------------------------------------------------------------------\n");
	}
	waitForKeyPress();
}

/* End of program */
void interface::exit() {
	clearScreen();
	running = false;
}

/* Program start and main handler */
void interface::run() {
	while (running) {
		switch (currentMenu) {
		case Menu::MAIN:
			displayMenu();
			handleChoiceMainMenu(getUserChoice());
			break;
		case Menu::BRUTEFORCE:
			broteforceUI();
			handleChoiceBruteforceMenu(getUserChoice());
			break;
		case Menu::SCANLINE:
			scanlineUI();
			handleChoiceScanlineMenu(getUserChoice());
		}
	}
}