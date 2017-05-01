#include <iostream>
#include <ctime>
#include <cstdlib>
#include "map.h"

using namespace std;



void map::generate(int mode) {

    // Diese Methode erstellt das Spielfeld, je nachdem welcher Schwierigkeitsgrad gewählt wurde.
    counter = 0;
    int s_schiffe, k_schiffe, z_schiffe, u_schiffe, pos;

    /*
        Dieser Switch entscheidet, wie viele Schiffe für welchen Schwierigkeitsgrad erzeugt werden sollen.

    */
    switch (mode) {
    case 0:
        s_schiffe = k_schiffe = z_schiffe = u_schiffe = 0;
        break;
    case 1:
        s_schiffe = 2;
        k_schiffe = 3;
        z_schiffe = 4;
        u_schiffe = 3;
        break;
    case 2:
        s_schiffe = 1;
        k_schiffe = 2;
        z_schiffe = 3;
        u_schiffe = 4;
        break;
    case 3:
        s_schiffe = 0;
        k_schiffe = 1;
        z_schiffe = 2;
        u_schiffe = 5;
        break;
    }
    //Array erstellen
    int** array = new int*[size];
    for (int h = 0; h < size; h++) {
        array[h] = new int[size];
        for (int w = 0; w < size; w++)
        {
            array[h][w] = 0;
        }
    }
    mid = array;

    for (int i = s_schiffe; i > 0; i--) {
        createSchlachtschiff();
    }
    for (int i = k_schiffe; i > 0; i--) {
        createKreuzer();
    }
    for (int i = z_schiffe; i > 0; i--) {
        createDestroyer();
    }
    for (int i = u_schiffe; i > 0; i--) {
        createUBoot();
    }
}

void map::print() {
    //Diese Methode gibt das eigentliche Spielfeld aus
    cout << "\t  A B C D E F G H I J \n\t _____________________\n";
    for (int h = 0; h < size; h++) {
        cout << h + 1 << "\t| ";
        for (int w = 0; w < size; w++)
        {
            cout << mid[h][w] << " ";
            if (w == size - 1)
                cout << "|";
        }
        cout << "\n";
    }
    cout << "\t|_____________________|\n";
    cout << flush;
}

void map::setShipPos(int length) {
    //Diese Methode erzeugt ein Schiff an einer zufälligen Stelle auf dem Spielfeld.
    //Die Länge des Schiffes wird dabei in die Tabelle eingetragen.



    bool success = false, check;
    int dir;
    int Xpos, Ypos;
    do {
        Xpos = (rand() % 10);	// random nummer von 0 bis 9
        Ypos = (rand() % 10);
        if (mid[Ypos][Xpos] == 0) {
            //Freies Feld
            dir = (rand() % 4);	// random number von 0 bis 4
            check = true;
            switch (dir) {
            case 0:	//Top
                for (int i = 0; i >= (-1 * (length - 2)); i--) {
                    if ((Ypos + i == 0)) {
                        check = false;
                        break;
                    }
                    else {
                        if (mid[Ypos + (i - 1)][Xpos] != 0) {
                            check = false;
                            break;
                        }
                    }
                }
                if (check) {
                    for (int i = 0; i >= (-1 * (length - 1)); i--) {
                        mid[Ypos + i][Xpos] = length;
                        counter++;
                    }
                    success = true;
                }
                break;
            case 1:	//Right
                for (int i = 0; i <= (length - 2); i++) {
                    if ((Xpos + i == size - 1)) {
                        check = false;
                        break;
                    }
                    else {
                        if (mid[Ypos][Xpos + (i + 1)] != 0) {
                            check = false;
                            break;
                        }
                    }
                }
                if (check) {
                    for (int i = 0; i <= (length - 1); i++) {
                        mid[Ypos][Xpos + i] = length;
                        counter++;
                    }
                    success = true;
                }
                break;
            case 2:	//Left
                for (int i = 0; i >= (-1 * (length - 2)); i--) {
                    if ((Xpos + i == 0)) {
                        check = false;
                        break;
                    }
                    else {
                        if (mid[Ypos][Xpos + (i - 1)] != 0) {
                            check = false;
                            break;
                        }
                    }
                }
                if (check) {
                    for (int i = 0; i >= (-1 * (length - 1)); i--) {
                        mid[Ypos][Xpos + i] = length;
                        counter++;
                    }
                    success = true;
                }
                break;
            case 3:	//Bottom
                for (int i = 0; i <= (length - 2); i++) {
                    if ((Ypos + i == size - 1)) {
                        check = false;
                        break;
                    }
                    else {
                        if (mid[Ypos + (i + 1)][Xpos] != 0) {
                            check = false;
                            break;
                        }
                    }
                }
                if (check) {
                    for (int i = 0; i <= (length - 1); i++) {
                        mid[Ypos + i][Xpos] = length;
                        counter++;
                    }
                    success = true;
                }
                break;
            }
        }
    } while (!success);
}

void map::createSchlachtschiff() {
    setShipPos(5);
}

void map::createKreuzer() {
    setShipPos(4);
}

void map::createDestroyer() {
    setShipPos(3);
}

void map::createUBoot() {
    setShipPos(2);
}
