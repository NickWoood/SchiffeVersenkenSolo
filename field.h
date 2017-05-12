#ifndef field_h
#define field_h

class field {
public:
	field(int size = 10);	//Konstruktor mit Defaultwerten
	void print();
	int getEntry(int x, int y);
	bool isInserted(int thing);
	void insert(int value, int x, int y);

	int** array;
private:
	int length = 0;
};

#endif
