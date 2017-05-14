class ship {
public:
	void initialize();
	bool isOnPos(int x, int y);
	void attack(int x, int y);
	void getPos();
	void addPos(int x, int y);

	int length = 0;
	int tiles = 0;
	int** pos;
};
