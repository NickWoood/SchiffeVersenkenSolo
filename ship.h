class ship {
public:
	void initialize();
	bool isOnPos(int x, int y);
	void destroy(int x, int y);
	void getPos();
	void addPos(int x, int y);

	int length;
	int tiles;
	int** pos;
	static int count;

};
