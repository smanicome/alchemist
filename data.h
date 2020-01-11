#ifndef DATA_H_
#define DATA_H_

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1400
#define BALL_RADIUS 50
#define ROW_COUNT 8
#define COL_COUNT 6
#define MAX_LEVEL 11

typedef struct position Position;
typedef struct field Field;
typedef struct cell Cell;
struct position {
	int alignement;
	int vertical;
	int left_level;
	int right_level;
};

struct field {
	int slots[ROW_COUNT][COL_COUNT];
	Position* pos;
};

struct cell {
	int x;
	int y;
	Cell* previous;
};


#endif