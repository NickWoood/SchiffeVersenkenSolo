
#include <iostream>
#include <string>
#include "map.cpp"



using namespace std;

int mode = 1;
int const array_size = 10;

void doSendMenu() {
    // Um den Schwierigkeitsgrad einstellen zu können.

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

	int length = (int)plc.length();
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
	srand(time(0)); //Für Zufallsgenerator
	cout << " --- Schiffe versenken (KonsolenEdition) --- \n" << endl;  //"Titel"

	doSendMenu();   //Gibt den Schwierigkeitsgrad wieder
	int* player_choice = 0;

	map m;
	m.size = array_size;
	m.generate(mode);
	map playerView;
	playerView.size = array_size;
	playerView.generate(0);
	playerView.counter = 50;


	while (playerView.counter >= 1) {
		//game loop
		cout << "\nDu hast noch " << playerView.counter << " Schüsse übrig.\n"<< "Du kannst noch " <<m.counter << " Schiffsteile treffen. \n" << flush;
		playerView.print();
		player_choice = getPlayerChoice();
		if(player_choice[0] == -1 && player_choice[1] == -1) {
            cout << "Printing map..." << endl;
            m.print();
            continue;
		}
		if (playerView.mid[player_choice[1] - 1][player_choice[0] - 1] == 1) {
			cout << "Du hast dieses Feld bereits attakiert." << endl;
			continue;
		}
		else {

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
		if (m.counter == 0)
			break;

	}
	if (m.counter == 0)
		cout << "Du hast gewonnen!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	else
		cout << "Du hast verloren :-(" << endl;

	//winner?

	system("pause");
	return 0;
}
