#include "player.h"

bool player::isEmptyField(int x, int y)
{
	if (getEntry(x, y) == 0)
		return true;

	return false;
}

void player::doMarkPos(int x, int y)
{
	insert(1, x, y);
}
