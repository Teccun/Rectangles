#pragma once
#include "algoritms/algoritms.h"

using namespace std;

class interface {
protected:
	bool running;
public:
	interface() : running(true) {}

	void displayMenu();

	int getUserChoice();

	void handleChoice(int choice);

	void problemConditionUI();

	void brutefireceUI();

	void scanlineUI();

	void exit();

	void run();

};