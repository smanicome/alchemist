#ifndef GAME_H_
#define GAME_H_

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT -1
#define NONE 4

#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "data.h"
#include "background.h"
#include "pair.h"
#include "display.h"
#include "fuse.h"
#include "animate.h"

/**
 * Handle the running game
 * Load resources
 * Loop until a slime exit the panel
 */
void game();

void initField(Field* field, Position* next2pair);

/**
 * Put slime at the lowest row available in the same column
 * If there aren't any, signal end of game
 * recursive calls
 */
int fillSlot(int slots[ROW_COUNT][COL_COUNT], int alignement, int previous_height, int height, int elt, MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]);

#endif
