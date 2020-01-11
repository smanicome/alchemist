#ifndef GAME_H_
#define GAME_H_

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#include "data.h"

void game();
void initField(Field* field, Position* next2peer);
void updateScreen(Field* field, int score, Position next2peer);
int fillSlot(int slots[ROW_COUNT][COL_COUNT], int alignement, int height, int elt);
int searchFuse(Field* field, int available_level[MAX_LEVEL]);
int fusePath(Field* field, int x, int y, int path[ROW_COUNT][COL_COUNT], int length);
void fuse(Field* field, int x, int y, int path[ROW_COUNT][COL_COUNT], int direction);

#endif