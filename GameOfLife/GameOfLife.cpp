#include "GameOfLife.h"

#include <iostream>
#include <string>
#include <ctime>
using namespace std;



bool game_of_life::slucajna_vrijednost()
{
	//Random odredivanje je li celija mrtva ili ziva (25% da je ziva)
	//True - Ziva / False - Mrtva
	bool random50;

	random50 = rand() % 2;

	if (random50 == 1) {
		bool random25;
		return rand() % 2;
	}
	else
		return false;
}

bool game_of_life::celija_zauzeta(int i, int y)
{
	//Slobodna - False / Zauzeta - True
	if (Vgeneracija[i][y] == false)
		return false;
	else
		return true;
}

int game_of_life::brojZivihSusjeda(int i, int y)
{
	int suma = 0;

	//Klasicni slucajevi
	if ((i >= 1 && i <= REDAKA - 2) && (y >= 1 && y <= STUPACA - 2)) {
		if (celija_zauzeta(i - 1, y - 1))
			suma++;
		if (celija_zauzeta(i - 1, y))
			suma++;
		if (celija_zauzeta(i - 1, y + 1))
			suma++;
		//
		if (celija_zauzeta(i, y - 1))
			suma++;
		//Izostavlja se trenutna celija
		if (celija_zauzeta(i, y + 1))
			suma++;
		//
		if (celija_zauzeta(i + 1, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y))
			suma++;
		if (celija_zauzeta(i + 1, y + 1))
			suma++;
	}

	//4 rubna slucaja (kutevi)
	//GL Gornji Lijevi
	if (i == 0 && y == 0) {
		if (celija_zauzeta(i, y + 1))
			suma++;
		if (celija_zauzeta(i + 1, y + 1))
			suma++;
		if (celija_zauzeta(i + 1, y))
			suma++;
	}
	//GD
	if (i == 0 && y == STUPACA - 1) {
		if (celija_zauzeta(i, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y))
			suma++;
	}
	//DL
	if (i == REDAKA - 1 && y == 0) {
		if (celija_zauzeta(i - 1, y))
			suma++;
		if (celija_zauzeta(i - 1, y + 1))
			suma++;
		if (celija_zauzeta(i, y + 1))
			suma++;
	}
	//DD
	if (i == REDAKA - 1 && y == STUPACA - 1) {
		if (celija_zauzeta(i - 1, y))
			suma++;
		if (celija_zauzeta(i - 1, y - 1))
			suma++;
		if (celija_zauzeta(i, y - 1))
			suma++;
	}


	//Ostali rubni slucajevi
	//Gornja traka
	if ((i == 0) && (y >= 1 && y <= STUPACA - 2)) {
		if (celija_zauzeta(i, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y))
			suma++;
		if (celija_zauzeta(i + 1, y + 1))
			suma++;
		if (celija_zauzeta(i, y + 1))
			suma++;
	}

	//Lijeva traka
	if ((i >= 1 && y <= REDAKA - 2) && (y == 0)) {
		if (celija_zauzeta(i - 1, y))
			suma++;
		if (celija_zauzeta(i - 1, y + 1))
			suma++;
		if (celija_zauzeta(i, y + 1))
			suma++;
		if (celija_zauzeta(i + 1, y + 1))
			suma++;
		if (celija_zauzeta(i + 1, y))
			suma++;
	}

	//Donja traka
	if ((i == REDAKA - 1) && (y >= 1 && y <= STUPACA - 2)) {
		if (celija_zauzeta(i, y - 1))
			suma++;
		if (celija_zauzeta(i - 1, y - 1))
			suma++;
		if (celija_zauzeta(i - 1, y))
			suma++;
		if (celija_zauzeta(i - 1, y + 1))
			suma++;
		if (celija_zauzeta(i, y + 1))
			suma++;
	}

	//Desna traka
	if ((i >= 1 && i <= REDAKA - 2) && (y == STUPACA - 1)) {
		if (celija_zauzeta(i - 1, y))
			suma++;
		if (celija_zauzeta(i - 1, y - 1))
			suma++;
		if (celija_zauzeta(i, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y - 1))
			suma++;
		if (celija_zauzeta(i + 1, y))
			suma++;
	}


	return suma;
}

game_of_life::game_of_life()
{
	//Ucitaj polje za igru (25% sanse da je celija ziva)
	//[Redci] - [Stupci]

	srand(time(nullptr));

	for (unsigned i = 0; i < REDAKA; i++) {
		for (unsigned y = 0; y < STUPACA; y++) {
			Vgeneracija[i][y] = slucajna_vrijednost();

		}
	}

}

void game_of_life::sljedeca_generacija()
{
	//Izbrisi sadrzaj nove generacije
	for (unsigned i = 0; i < REDAKA; i++) {
		for (unsigned y = 0; y < STUPACA; y++) {
			Vsljedeca_generacija[i][y] = false;
		}
	}

	/*
	Izracunaj kako ce izgledati sljedece polje i spremi u listu
	1. Survive      2,3					(ako je trenutno ziva i ima 2 ili 3 ziva susjeda onda prezivi)
	2. Die         <2 || >3				(ako je trenutno ziva i ima manje od 2 ili vise od 3 ziva susjeda onda umire)
	3. Birth        3 susjedna ziva		(ako je trenutno mrtva i ima tocno 3 ziva susjeda onda se rodi)
	*/

	for (unsigned i = 0; i < REDAKA; i++) {
		for (unsigned y = 0; y < STUPACA; y++) {
			//1.
			if (Vgeneracija[i][y] == true && (brojZivihSusjeda(i, y) == 2 || brojZivihSusjeda(i, y) == 3))
				Vsljedeca_generacija[i][y] = true;
			//2.
			else if (Vgeneracija[i][y] == true && (brojZivihSusjeda(i, y) < 2 || brojZivihSusjeda(i, y) > 3))
				Vsljedeca_generacija[i][y] = false;
			//3.
			else if (Vgeneracija[i][y] == false && (brojZivihSusjeda(i, y) == 3))
				Vsljedeca_generacija[i][y] = true;
			else
				Vsljedeca_generacija[i][y] = Vgeneracija[i][y];
		}
	}
	//Upisi novu generaciju u trenutnu

	for (unsigned i = 0; i < REDAKA; i++) {
		for (unsigned y = 0; y < STUPACA; y++) {
			Vgeneracija[i][y] = Vsljedeca_generacija[i][y];
		}
	}


}

void game_of_life::iscrtaj()
{
	//Ispisi sadrzaj  [Redci]i  [Stupci]y , Zakomentiran je ispis broja retka i stupca
	for (int i = 0; i < REDAKA; i++) {

		/*
		if (i == 0) {
			cout << "\t 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9 1 3 5 7 9" << endl;
			cout << "\t0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0 2 4 6 8" << endl << endl;
		}
		cout << i + 1 << "\t";
		*/
		for (int y = 0; y < STUPACA; y++) {
			if (Vgeneracija[i][y])
				cout << "*";
			else
				cout << "-";

		}
		cout << endl;
	}
}
