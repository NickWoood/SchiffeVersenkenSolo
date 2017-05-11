#include "field.h"
#include "ship.h"

class map : public field {
public:

	void attackField(int x, int y);
	void createShipOnRandomPos(int length, ship* j, int index);
	void generateShips(int s, int k, int z, int u);
	int getShipCount();
	void refresh();

	ship *s_schiffe;
	int s_schiffe_count;
	ship *k_schiffe;
	int k_schiffe_count;
	ship *z_schiffe;
	int z_schiffe_count;
	ship *u_schiffe;
	int u_schiffe_count;
};
