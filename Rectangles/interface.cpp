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

void interface::handleChoice(int choice) {
	switch (choice){
	case 1:
		problemConditionUI();
		break;
	case 2:
		brutefireceUI();
		break;
	case 3:
		scanlineUI();
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

void interface::brutefireceUI() {
	return;
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
		displayMenu();
		int choice = getUserChoice();
		if (choice != -1)
			handleChoice(choice);
	}
}