#include "game.h"
#include <iostream>
#include "player.h"
#include "map.h"
#include <string>

using namespace std;
void game::menu()
{
	cout << "Bitte waehle einen Schwierigkeitsgrad.\n";
	cout << "[1] leicht\n" << "[2] mittel\n" << "[3] schwer\n" << endl;
	cin >> mode;

	if (!cin) {
		mode = 0;
		cin.clear();
		cout << "Fehler: Bitte eine Zahl von 1 bis 3 eingeben." << endl;
		menu();
	}
	if (!(mode > 0 && mode < 4)) {
		mode = 0;
		cout << "Fehler: Bitte eine Zahl von 1 bis 3 eingeben." << endl;
		menu();
	}
}

void game::initialize()
{
	cout << " --- Schiffe versenken (KonsolenEdition) --- \n" << endl; //"Titel"
	menu();
	run();
}

void game::run()
{
	running = true;
	player PlayerMap;
	map ShipMap;
	switch (mode) {
	case 1:
		//ShipMap.generateShips(2, 3, 4, 3);
		ShipMap.generateShips(1, 3, 4, 3);
		break;
	case 2:
		ShipMap.generateShips(1, 2, 3, 4);
		break;
	case 3:
		ShipMap.generateShips(0, 1, 2, 5);
		break;
	}

	while (PlayerMap.shots >= 1 && running) {
		//Game Loop
		cout << "\nDu hast noch " << PlayerMap.shots << " Schuesse übrig.\n" << "Du kannst noch " << ShipMap.ship_count << " Schiffe treffen. \n" << flush;
		PlayerMap.print();
		ShipMap.print();


        ShipMap.refresh();
		int* choice = getPlayerChoice();
		if (!PlayerMap.isEmptyField(choice[0], choice[1])) {
			//Falls der Spieler das Feld schon getroffen hat.
			cout << "Du hast dieses Feld bereits attakiert." << endl;
			continue;
		}
		else {
			//Trage den Angriff in die PlayerMap ein.
			PlayerMap.doMarkPos(choice[0], choice[1]);
			//Überprüfe ob ein Schiffe der attakierten Position entspricht.
			ShipMap.attackField(choice[0], choice[1]);
		}
		if (ShipMap.ship_count == 0) {
			cout << "Du hast alle Schiffe getoffen !" << endl;
			stop();
		}

		PlayerMap.shots--;
	}
}

void game::stop()
{
	running = false;
}

int * game::getPlayerChoice()
{
	/*
	Diese Methode soll die Eingabe vom Spieler lesen.
	Bei einer ungültigen Eingabe gibt es aber noch einen bug.
	Da diese Methode aber bei der Benutzung von Sprites sowieso rausfliegt, bleibt sie erstmal so.
	*/
	int* choice = new int[2];
	choice[0] = 0;
	choice[1] = 0;
	string plc;
	plc.clear();
	cout << "Bitte gib dein Ziel ein ..." << endl;
	cin >> plc;

	if (plc == "map.print") {
		choice[0] = -1;
		choice[1] = -1;
		return choice;
	}

	if (plc.length() < 2 || plc.length() > 3) {
		cout << "Fehlerhafte Eingabe. [Error C1]" << endl;
		getPlayerChoice();
	}

	/* Der rekursive Aufruf verursacht noch einen bug.
	*/

	if (plc.at(0) == 'A' || plc.at(0) == 'B' || plc.at(0) == 'C' || plc.at(0) == 'D' || plc.at(0) == 'E' || plc.at(0) == 'F' || plc.at(0) == 'G' || plc.at(0) == 'H' || plc.at(0) == 'I' || plc.at(0) == 'J')
		choice[0] = plc[0] - '0' - 16;
	else {
		cout << "Fehlerhafte Eingabe. [Error C2]" << endl;
		getPlayerChoice();
	}

	if (plc.length() == 3) {
		if ((plc.at(1) == '1' || plc.at(1) == '2' || plc.at(1) == '3' || plc.at(1) == '4' || plc.at(1) == '5' || plc.at(1) == '6' || plc.at(1) == '7' || plc.at(1) == '8' || plc.at(1) == '9') && plc.at(2) == '0') {
			choice[1] = 10;
		}
		else {
			cout << "Fehlerhafte Eingabe. [Error C3]" << endl;
			getPlayerChoice();
		}
	}
	else {
		if (plc.at(1) == '1' || plc.at(1) == '2' || plc.at(1) == '3' || plc.at(1) == '4' || plc.at(1) == '5' || plc.at(1) == '6' || plc.at(1) == '7' || plc.at(1) == '8' || plc.at(1) == '9') {
			choice[1] = plc[1] - '0';
		}
		else {
			cout << "Fehlerhafte Eingabe. [Error C4]" << endl;
			getPlayerChoice();
		}
	}



	return choice;
}
