#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

class field {
public:
	field(int size = 10);	//Konstruktor mit Defaultwerten
	void print();
	int getEntry(int x, int y);
	bool isInserted(int thing);
	void insert(int value, int x, int y);
	void clean();

	int** arrayCollect;
	int length = 0;
};

#endif
