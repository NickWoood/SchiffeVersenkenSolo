#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
class map {

public:
	int** mid;
	int size;
	int counter;




	int** generateEmpty2DArray(int t) {
		int** array = new int*[t];
		for (int h = 0; h < t; h++) {
			array[h] = new int[t];
			for (int w = 0; w < t; w++)
			{
				array[h][w] = 0;
			}
		}
		return array;
	}



	void generate(int mode) {
		counter = 0;
		int s_schiffe, k_schiffe, z_schiffe, u_schiffe, pos;
		int** map2D = generateEmpty2DArray(size);
	//	int s_size = 5, k_size = 4, z_size = 3, u_size = 2;

		// Schiffe
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
		for (int h = 0; h < size; h++) {
			map2D[h] = new int[size];
			for (int w = 0; w < size; w++)
			{
				map2D[h][w] = 0;
			}
		}
		mid = map2D;

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

	void print() {
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
	void setShipPos(int length) {
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

	void createSchlachtschiff() {
		setShipPos(5);
	}

	void createKreuzer() {
		setShipPos(4);
	}

	void createDestroyer() {
		setShipPos(3);
	}

	void createUBoot() {
		setShipPos(2);
	}
};
