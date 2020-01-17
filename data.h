#ifndef DATA_H_
#define DATA_H_

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1400
#define SLIME_SIZE 100
#define ROW_COUNT 8
#define COL_COUNT 6
#define MAX_LEVEL 11
#define STANDING_FRAMES 12
#define ROLLING_FRAMES 21
#define JUMPING_FRAMES 4

typedef struct position Position;
typedef struct field Field;

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


#endif