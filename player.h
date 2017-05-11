#include "field.h"

class player : public field {
public:
	int shots = 50;
	bool isEmptyField(int x, int y);
	void doMarkPos(int x, int y);


};

