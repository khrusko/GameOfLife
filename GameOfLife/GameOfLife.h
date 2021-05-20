#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class game_of_life {
private:
	static const unsigned int STUPACA = 40;
	static const unsigned int REDAKA = 20;
	bool Vgeneracija[REDAKA][STUPACA];
	bool Vsljedeca_generacija[REDAKA][STUPACA];
	bool slucajna_vrijednost();
	bool celija_zauzeta(int i, int y);
	int brojZivihSusjeda(int i, int y);

public:
	game_of_life();
	void sljedeca_generacija();
	void iscrtaj();
};

