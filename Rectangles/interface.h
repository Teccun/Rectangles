#pragma once
#include "myalgoritm.h"
#include "workwithfiles/workwithfiles.h"
#include "algoritms/broteforce.h"

using namespace std;

class interface {
protected:
	bool running;
	int menu = 0;
public:
	interface() : running(true), menu(0) {}

	void displayMenu();

	int getUserChoice();

	void handleChoiceMainMenu(int choice);
	void handleChoiceBruteforceMenu(int choice);

	void problemConditionUI();

	void broteforceUI();
	void broteforceReadFromFile();
	void broteforceTestClass();
	void broteforceGenerate();

	void returnToMainMenu();

	void scanlineUI();

	void exit();

	void run();

};