#ifndef DATA_H_
#define DATA_H_

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1400
#define BALL_RADIUS 50

typedef struct position {
    int alignement;
    int vertical;
    int left_level;
    int right_level;
} Position;

typedef struct field {
    int cases[8][6];
    Position pos;
} Field;

typedef struct cell {
    int index;
    struct cell* next;
} Cell;

typedef Cell* Voisinage;

#endif