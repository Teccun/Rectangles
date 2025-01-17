#include "interface.h"

#include <conio.h>

void interface::displayMenu() {
	system("cls");
	printf("1. Problem condition\n");
	printf("2. Bruteforce\n");
	printf("3. Scanline\n");
	printf("4. Exit\n\n");
}

int interface::getUserChoice() {
	int choice = 0;
	std::cout << "-> ";
	std::cin >> choice;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
		return -1;
	}

	return (choice);
}

void interface::handleChoiceMainMenu(int choice) {
	switch (choice){
	case 1:
		problemConditionUI();
		break;
	case 2:
		broteforceUI();
		menu = 1;
		break;
	case 3:
		scanlineUI();
		menu = 2;
		break;
	case 4:
		exit();
		break;
	default:
		std::cout << "Неверный выбор. Попробуйет снова.\n";
		_getch();
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
		returnToMainMenu();
		break;
	default:
		std::cout << "Неверный выбор. Попробуйте снова.\n";
		_getch();
		break;
	}
}


void interface::problemConditionUI() {
	system("cls");
	std::cout << "Прямоугольники\n";
	std::cout << "На плоскости задано N прямоугольников. Найти точки, покрытые не менее чем k из них.\n";
	std::cout << "Входные данные – координаты прямоугольников ( левый нижний и правый верхний угол) и k.\n";
	std::cout << "Выход – координаты прямоугольников, образованные точками, покрытыми не менее чем k прямоугольниками.\n";

	std::cout << "\n";
	std::cout << "Нажмите на любую клавишу для выхода.\n";
	_getch();

	return;
}

void interface::returnToMainMenu() {
	system("cls");
	menu = 0;
	return;
}

void interface::broteforceUI() {
	system("cls");
	printf("1. Read rectangles from file\n");
	printf("2. Use standart tests\n");
	printf("3. Generate random rectangles for test\n");
	printf("4. <--\n\n");
	return;
}
void interface::broteforceReadFromFile() {
	system("cls");
	std::cout << "Используйте файл in.txt для записывания данных\n";
	std::cout << "Нажмите любую клавишу после записи информации\n";
	std::cout << "(Просьба записывать данные правильно: x1 y1 x2 y2 - числа с плавающей точкой)\n";
	_getch();

	std::vector<rectangle> rect = readFile();
	std::cout << "\nВведите значение k.\n";

	int k;
	std::cin >> k;
	broteforce alg(rect, k);
	alg.execute();

	std::cout << "\nНажмите любую клваишу, чтобы вернуться.\n";
	_getch();
	return;
}
void interface::broteforceTestClass() {

}
void interface::broteforceGenerate() {

}

void interface::scanlineUI() {
	return;
}

void interface::exit() {
	system("cls");
	running = false;
	return;
}

void interface::run() {
	while (running) {
		if (menu == 0)
			displayMenu();
		if (menu == 1)
			broteforceUI();
		int choice = getUserChoice();
		if (choice != -1) {
			if (menu == 0)
				handleChoiceMainMenu(choice);
			if (menu == 1) 
				handleChoiceBruteforceMenu(choice);
			if (menu == 2)
				menu = 0;
		}
	}
}