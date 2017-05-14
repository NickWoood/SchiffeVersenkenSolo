#include "map.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

void map::attackField(int x, int y)
{
	if (ship_count > 0) {
		for (int q = 1; q <= ship_count; q++) {
			s_objects[q - 1].attack(x, y);
		}
	}
	refresh();
}


void map::createShipOnRandomPos(int length,ship* j, int index)
{
	time_t t;
	time(&t);
	srand((unsigned int)t);

	j[index].length = length;
	j[index].initialize();
	bool success = false, check;
	int dir, xpos, ypos;
	do {
		xpos = (rand() % 10)+1; // Zahl zwischen 1 und 10
		ypos = (rand() % 10)+1;
		if (getEntry(xpos, ypos) == 0) {
			//Wenn es ein freies Feld ist
			dir = (rand() % 4); // Zahl zwischen 0 und 3
			check = true;
			switch (dir) {
			case 0:
				//Norden
				if (ypos - length >= 0) {
					for (int i = 0; i < length; i++) {
						if (getEntry(xpos, ypos - i) != 0) {
							check = false;
							break;
						}
					}
					if (check) {
						for (int i = 0; i < length; i++) {
							j[index].addPos(xpos, ypos - i);
							j[index].tiles++;
							insert(length, xpos, ypos - i);
						}
						success = true;
					}
				}
				break;
			case 1:
				//Osten
				if (xpos + length <= 10) {
					for (int i = 0; i < length; i++) {
						if (getEntry(xpos+i, ypos) != 0) {
							check = false;
							break;
						}
					}
					if (check) {
						for (int i = 0; i < length; i++) {
							j[index].addPos(xpos+i, ypos);
							j[index].tiles++;
							insert(length, xpos + i, ypos);
						}
						success = true;
					}
				}
				break;
			case 2:
				//Süden
				if (ypos + length <= 10) {
					for (int i = 0; i < length; i++) {
						if (getEntry(xpos, ypos + i) != 0) {
							check = false;
							break;
						}
					}
					if (check) {
						for (int i = 0; i < length; i++) {
							j[index].addPos(xpos, ypos + i);
							j[index].tiles++;
							insert(length, xpos, ypos + i);
						}
						success = true;
					}
				}
				break;
			case 3:
				//Westen
				if (xpos - length >= 0) {
					for (int i = 0; i < length; i++) {
						if (getEntry(xpos - i, ypos) != 0) {
							check = false;
							break;
						}
					}
					if (check) {
						for (int i = 0; i < length; i++) {
							j[index].addPos(xpos - i, ypos);
							j[index].tiles++;
							insert(length, xpos - i, ypos);
						}
						success = true;
					}
				}
				break;
			}
		}

	} while (!success);
}

void map::generateShips(int s, int k, int z, int u)
{
	std::cout << "Erstelle " << s << " Schlachtschiffe, " << k << " Kreuzer, " << z << " Zerstoerer und " << u << " U-Boote." << std::endl;
    s_objects = new ship[(s+k+z+u)];
	ship_count += (s + k + z + u);
	int j = 0;
	for (s; s > 0; s--) {
		createShipOnRandomPos(5, s_objects, j);
		j++;
	}
	for (k; k > 0; k--) {
		createShipOnRandomPos(4, s_objects, j);
		j++;
	}
	for (z; z > 0; z--) {
		createShipOnRandomPos(3, s_objects, j);
		j++;
	}
	for (u; u > 0; u--) {
		createShipOnRandomPos(2, s_objects, j);
		j++;
	}
}

void map::refresh()
{
	clean();
	for (int x = 1; x <= 10; x++) {
		for (int y = 1; y <= 10; y++) {
			for (int q = 1; q <= ship_count; q++) {
				if (s_objects[q - 1].isOnPos(x, y)) {
					insert(s_objects[q - 1].length, x, y);
				}
			}
		}
	}
}
