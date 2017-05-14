#include "field.h"
#include "ship.h"

class map : public field {
public:
	void attackField(int x, int y);
	void createShipOnRandomPos(int length, ship* j, int index);
	void generateShips(int s, int k, int z, int u);
	void refresh();

	ship *s_objects;
	int ship_count = 0;
};
