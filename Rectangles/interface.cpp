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