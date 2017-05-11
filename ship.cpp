#include "ship.h"
#include <iostream>

using namespace std;

void ship::initialize()
{
	pos = new int*[length];
	for (int h = 0; h < length; h++) {
		pos[h] = new int[2];
		pos[h][0] = -1;
		pos[h][1] = -1;
	}
}

bool ship::isOnPos(int x, int y)
{
	for (int h = 0; h < length; h++) {
		if (pos[h][0] == x && pos[h][1] == y)
			return true;
	}
	return false;
}

void ship::destroy(int x, int y)
{
	for (int h = 0; h < length; h++) {
		if (pos[h][0] == x && pos[h][1] == y) {
			pos[h][0] = -1;
			pos[h][1] = -1;
		}
	}
}

void ship::getPos() 
{
	for (int h = 0; h < length; h++) {
		cout << pos[h][0] << endl;
		cout << pos[h][1] << endl;
	}
}

void ship::addPos(int x, int y)
{
	for (int h = 0; h < length; h++) {
		if (pos[h][0] == -1 && pos[h][1] == -1) {
			pos[h][0] = x;
			pos[h][1] = y;
			break;
		}
		cout << "Adding " << x << " and " << y << " ! " << endl;
	}
}
