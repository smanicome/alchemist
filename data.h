#ifndef DATA_H_
#define DATA_H_

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1400
#define BALL_RADIUS 50
#define COL_SIZE 8
#define ROW_SIZE 6

typedef struct position Position;
typedef struct field Field;

struct position {
    int alignement;
    int vertical;
    int left_level;
    int right_level;
    int top_level;
    int bottom_level;
};

struct field {
    int slots[ROW_SIZE][COL_SIZE];
    Position* pos;
};

#endif