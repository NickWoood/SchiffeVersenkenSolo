#include <iostream>
#include <string>
#include "map.h"
#include <cstdlib>



using namespace std;

int mode = 1;
int const array_size = 10;

void doSendMenu() {
    // Diese Methode fragt den Spieler einfach nur ab, welchen Schwierigkeitsgrad er haben möchte.
    // Bei zukünftiger Implementierung lohnt es sich möglicherweise eine Klasse für das Menü zu erzeugen.

	cout << "Bitte wähle einen Schwierigkeitsgrad.\n";
	cout << "[1] leicht\n" << "[2] mittel\n" << "[3] schwer\n" << endl;
	cin >> mode;

	if (!cin) {
		mode = 0;
		cin.clear();
		cout << "Fehler: Bitte eine Zahl von 1 bis 3 eingeben." << endl;
		doSendMenu();
	}
	if (!(mode > 0 && mode < 4)) {
		mode = 0;
		cout << "Fehler: Bitte eine Zahl von 1 bis 3 eingeben." << endl;
		doSendMenu();
	}
}
int* getPlayerChoice() {
    /*
    Diese Methode soll die Eingabe vom Spieler lesen.
    Bei einer ungültigen Eingabe gibt es aber noch einen bug.
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

int main() {
	cout << " --- Schiffe versenken (KonsolenEdition) --- \n" << endl;  //"Titel"

	doSendMenu();   //Gibt den Schwierigkeitsgrad wieder
	int* player_choice = 0;

	/*
	Hier werden im Grund zwei maps erstellt:
        - m: Diese 2D Tabelle enthält alle zufallsgenerierten Schiffe.
        - playerView: Diese Tabelle sammelt die Schüsse vom Spieler und enthält keine Schiffspositionen.
    Nach jedem Schuss wird playerView mit m verglichen, um zu sehen, ob es einen Treffer gab.
	*/
	map m;
	m.size = array_size;
	m.generate(mode);
	map playerView;
	playerView.size = array_size;
	playerView.generate(0);
	playerView.counter = 50;


	while (playerView.counter >= 1) {
		/*
            game loop
            Diese While-Schleife wird solange ausgeführt, bis playerView.counter (repräsentiert die Anzahl der Schüsse vom Spieler, < 1 ist.
		*/
		cout << "\nDu hast noch " << playerView.counter << " Schüsse übrig.\n"<< "Du kannst noch " <<m.counter << " Schiffsteile treffen. \n" << flush;
		playerView.print();
		player_choice = getPlayerChoice();

		//Diese kleine Abfrage dient nur Testzwecken. Mit der Eingabe "map.print" ist es möglich, eine aufgedeckte Karte auszugeben.
		if(player_choice[0] == -1 && player_choice[1] == -1) {
            cout << "Printing map..." << endl;
            m.print();
            continue;
		}

		//Hier wird geprüft, ob der Spieler das eingegebene Feld bereits attakiert hat.
		if (playerView.mid[player_choice[1] - 1][player_choice[0] - 1] == 1) {
			cout << "Du hast dieses Feld bereits attakiert." << endl;
			continue;
		}
		else {
            //Falls der Spieler dieses Feld noch nicht getroffen hat, wird m mit playerView verglichen und möglicherweise ein Treffer ausgegeben.
			if (m.mid[player_choice[1] - 1][player_choice[0] - 1] != 0) {
				playerView.mid[player_choice[1] - 1][player_choice[0] - 1] = m.mid[player_choice[1] - 1][player_choice[0] - 1];
				cout << "Du hast was getroffen!" << endl;
				m.counter--;
			}
			else
				playerView.mid[player_choice[1] - 1][player_choice[0] - 1] = 1;
		}

		player_choice = 0;
		playerView.counter--;

		//m.counter entspricht der Anzahl an Schiffsteilen. Falls sie auf 0 sinkt, ist das Spiel gewonnen und der Loop wird unterbrochen.
		if (m.counter == 0)
			break;

	}
	//Schleife wird beendet, wenn der Spieler keine Schüsse mehr hat oder keine Schiffsteile mehr übrig sind.
	if (m.counter == 0)
		cout << "Du hast gewonnen!" << endl;
	else
		cout << "Du hast verloren :-(" << endl;



	system("pause");
	return 0;
}
