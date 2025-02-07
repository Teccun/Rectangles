#pragma once
#include "workwithfiles/workwithfiles.h"
#include "algoritms/scanline_bruteforce.h"
#include "algoritms/scanline_fast.h"
#include "algoritms/native.h"
#include "test.h"
#include <conio.h>

using namespace std;

class interface {
protected:
	bool running;
	enum class Menu {
		MAIN,
		BRUTEFORCE,
		SCANLINE,
	};
	Menu currentMenu;
public:
	interface() : running(true), currentMenu(Menu::MAIN) {}

	void clearScreen() {
		system("cls");
	}
	void waitForKeyPress() {
		std::cout << "\nНажмите любую клавишу для продолжения...";
		_getch();
	}

	void displayMenu();

	int getUserChoice();

	void handleChoiceMainMenu(int choice);
	void handleChoiceBruteforceMenu(int choice);
	void handleChoiceScanlineMenu(int choice);

	void problemConditionUI();

	void broteforceUI();
	void broteforceReadFromFile();
	void broteforceTestClass();
	void broteforceGenerate();

	//void returnToMainMenu();

	void scanlineUI();
	void scanlineReadFromFile();
	void scanlineTestClass();
	void scanlineGenerate();

	void algorithmComparison();
	void algorithmBaseComparison();
	void algorithmProgressivComparison();

	void exit();

	void run();

};