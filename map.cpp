#include "map.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

void map::attackField(int x, int y)
{
	/*
	*Alle Schiffe sollen in einer Tabelle gespeichert werden.
	*Dadurch wird es in dieser Methode nur noch eine Schleife geben.
	*/
	bool hit = false;
	for (int i = 1; i <= s_schiffe_count; i++) {
		if (s_schiffe[i - 1].isOnPos(x, y)) {
			s_schiffe[i - 1].destroy(x, y);
			hit = true;
			break;
		}
	}

	for (int i = 1; i <= k_schiffe_count; i++) {
		if (k_schiffe[i - 1].isOnPos(x, y)) {
			k_schiffe[i - 1].destroy(x, y);
			hit = true;
			break;
		}
	}
	for (int i = 1; i <= u_schiffe_count; i++) {
		if (u_schiffe[i - 1].isOnPos(x, y)) {
			u_schiffe[i - 1].destroy(x, y);
			hit = true;
			break;
		}
	}
	for (int i = 1; i <= z_schiffe_count; i++) {
		if (z_schiffe[i - 1].isOnPos(x, y)) {
			z_schiffe[i - 1].destroy(x, y);
			hit = true;
			break;
		}
	}

	if (hit) {
		std::cout << "Du hast was getroffen !" << std::endl;
		refresh();
	}
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
	if(s > 0)
		s_schiffe = new ship[s]; 
	for (s;  s > 0; s--) {
		createShipOnRandomPos(5, s_schiffe, s-1);
		s_schiffe_count++;

	}
	if (k > 0)
		k_schiffe = new ship[k];
	for (k; k > 0; k--) {
		createShipOnRandomPos(4, k_schiffe, k-1);
		k_schiffe_count++;
	}
	if (z > 0)
		z_schiffe = new ship[z];
	for (z; z > 0; z--) {
		createShipOnRandomPos(3, z_schiffe, z-1);
		z_schiffe_count++;
	}
	if (u > 0)
		u_schiffe = new ship[u];
	for (u; u > 0; u--) {
		createShipOnRandomPos(2, u_schiffe,u -1);
		u_schiffe_count++;
	}

}

int map::getShipCount()
{
	return (s_schiffe_count + k_schiffe_count + z_schiffe_count + u_schiffe_count);
}

void map::refresh()
{
	/*
	*Diese Methode wird noch verkleinert (weniger Schleifen).
	*Momentan ist hier noch irgendwo ein bug, der zu fehlerhaften Map-Daten führt.
	*/
	for(int xpos = 1; xpos <= 10; xpos++) {
		for (int ypos = 1; ypos <= 10; ypos++) {
			for (int i = 1; i <= s_schiffe_count; i++) {
				if (s_schiffe[i - 1].isOnPos(xpos, ypos)) {
					insert(5, xpos, ypos);
				}
				else
					insert(0, xpos, ypos);
			}
			for (int i = 1; i <= k_schiffe_count; i++) {
				if (k_schiffe[i - 1].isOnPos(xpos, ypos)) {
					insert(4, xpos, ypos);
				}
				else
					insert(0, xpos, ypos);
			}
			for (int i = 1; i <= u_schiffe_count; i++) {
				if (u_schiffe[i - 1].isOnPos(xpos, ypos)) {
					insert(2, xpos, ypos);
				}
				else
					insert(0, xpos, ypos);
			}
			for (int i = 1; i <= z_schiffe_count; i++) {
				if (z_schiffe[i - 1].isOnPos(xpos, ypos)) {
					insert(3, xpos, ypos);
				}
				else
					insert(0, xpos, ypos);
			}
		}
	}
}
