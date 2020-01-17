#ifndef PAIR_H_
#define PAIR_H_

#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "background.h"
#include "display.h"
#include "data.h"
#include "animate.h"


void generatePair(Position* pos, int available_level[MAX_LEVEL-2]);
void nextPair(
	Field* field, 
	int score, 
	Position next2pair, 
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1], 
	MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1],
	MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]
);
int fallPair(Field* field, MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]);

#endif