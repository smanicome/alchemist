#ifndef GAME_H_
#define GAME_H_

#include "data.h"

void game();
void initField(Field* field);
void generatePair(Position* pos);
void updateScreen(Field* field, int score);
void nextPair(Field* field, int score);
int fallPair(Field* field);
int fillSlot(int slots[ROW_SIZE][COL_SIZE], int alignement, int height, int elt);
int searchFuse(Field* field);
int fusePath(Field* field, int x, int y, int path[ROW_SIZE][COL_SIZE], int* core_x, int* core_y);
void fuse(Field* field, int path[ROW_SIZE][COL_SIZE]);

#endif