// MS5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/* ------------------------------------------------------
Final project Milestone 51
Filename: main.cpp
Version 1.0
-----------------------------------------------------------
Date          Reason
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"

using namespace sdds;
using namespace std;

void copyfile(const char* to, const char* from);
void displayFile(const char* file);

int main() {
	copyfile("data.dat", "data51.dat");
	ut.testMode();
	ut.skip_sku();
	
	AidMan aidMan;
	aidMan.run();
	
	displayFile("data.dat");
	return 0;
}

void displayFile(const char* file) {
	ifstream in(file);
	char ch;
	cout << "File: " << file << endl;
	while (in.get(ch)) cout << ch;
}

void copyfile(const char* to, const char* from) {
	std::ifstream in(from);
	std::ofstream out(to);
	char ch;
	while (in.get(ch)) out.put(ch);
}
