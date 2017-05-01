class map {

public:
	int** mid;
	int size;
	int counter;

	int** generateEmpty2DArray(int t);
	void generate(int mode);
    void print();
    void setShipPos(int length);
    void createSchlachtschiff();
    void createKreuzer();
    void createDestroyer();
    void createUBoot();
};
