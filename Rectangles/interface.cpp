#include "interface.h"

/* Text data (menus and other information) */
void interface::displayMenu() {
	clearScreen();
	printf("=== Main menu ===\n");
	printf("1. Problem condition\n");
	printf("2. Bruteforce\n");
	printf("3. Scanline\n");
	printf("4. Algorithm comparison\n");
	printf("5. Exit\n\n");
}
void interface::problemConditionUI() {
	clearScreen();
	printf("=== Условие задачи ===\n");
	printf("Прямоугольники\n");
	printf("На плоскости задано N прямоугольников. Найти точки, покрытые не менее чем k из них.\n");
	printf("Входные данные – координаты прямоугольников ( левый нижний и правый верхний угол) и k.\n");
	printf("Выход – координаты прямоугольников, образованные точками, покрытыми не менее чем k прямоугольниками.\n");
	waitForKeyPress();
}
void interface::broteforceUI() {
	clearScreen();
	printf("=== Brute-force method menu ===\n");
	printf("1. Read rectangles from file\n");
	printf("2. Use standart tests\n");
	printf("3. Generate random rectangles for test\n");
	printf("4. Return to Main menu\n\n");
}
void interface::scanlineUI() {
	clearScreen();
	printf("=== Scanline method menu ===\n");
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
		exit();
		break;
	default:
		printf("Неверный выбор. Попробуйет снова.\n");
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
		std::cout << "Неверный выбор. Попробуйте снова.\n";
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
		std::cout << "Неверный выбор. Попробуйте снова.\n";
		waitForKeyPress();
		break;
	}
}

/* Reading data from .txt file */
void interface::broteforceReadFromFile() {
	clearScreen();
	printf("=== Read from file ===\n");
	printf("Введите файл с расширением .txt, в котором находися информация\n");
	printf("(Просьба записывать данные правильно: x1 y1 x2 y2 - числа с плавающей точкой)\n"); std::string namefile;
	std::cin >> namefile;

	std::vector<rectangle> rect = readFile(namefile);
	std::cout << "\nВведите значение k: ";

	int k;
	std::cin >> k;
	bruteforce alg(rect, k);
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
	printf("=== Brote-force with random rectangles ===\n");
	printf("Введи (целое) число прямоугольников и границы (minX, maxX, minY, maxY тип float) для возможной генерации\n");
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
	printf("Введите файл с расширением .txt, в котором находися информация\n");
	printf("(Просьба записывать данные правильно: x1 y1 x2 y2 - числа с плавающей точкой)\n"); std::string namefile;
	std::cin >> namefile;

	std::vector<rectangle> rect = readFile(namefile);
	std::cout << "\nВведите значение k: ";

	int k;
	std::cin >> k;
	scanline alg(rect, k);
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
	printf("=== Scanline with random rectangles ===\n");
	printf("Введи (целое) число прямоугольников и границы (minX, maxX, minY, maxY тип float) для возможной генерации\n");
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
	printf("Введи (целое) число прямоугольников и границы (minX, maxX, minY, maxY тип float) для возможной генерации\n");
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