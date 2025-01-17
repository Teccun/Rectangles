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
		std::cout << "�������� �����. ���������� �����.\n";
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
		std::cout << "�������� �����. ���������� �����.\n";
		_getch();
		break;
	}
}


void interface::problemConditionUI() {
	system("cls");
	std::cout << "��������������\n";
	std::cout << "�� ��������� ������ N ���������������. ����� �����, �������� �� ����� ��� k �� ���.\n";
	std::cout << "������� ������ � ���������� ��������������� ( ����� ������ � ������ ������� ����) � k.\n";
	std::cout << "����� � ���������� ���������������, ������������ �������, ��������� �� ����� ��� k ����������������.\n";

	std::cout << "\n";
	std::cout << "������� �� ����� ������� ��� ������.\n";
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
	std::cout << "����������� ���� in.txt ��� ����������� ������\n";
	std::cout << "������� ����� ������� ����� ������ ����������\n";
	std::cout << "(������� ���������� ������ ���������: x1 y1 x2 y2 - ����� � ��������� ������)\n";
	_getch();

	std::vector<rectangle> rect = readFile();
	std::cout << "\n������� �������� k.\n";

	int k;
	std::cin >> k;
	broteforce alg(rect, k);
	alg.execute();

	std::cout << "\n������� ����� �������, ����� ���������.\n";
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