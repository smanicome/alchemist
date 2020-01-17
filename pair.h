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

/**
 * Generate next pair base on the users progression
 *
 */
void generatePair(Position* pos, int available_level[MAX_LEVEL-2]);

/**
 * Let the user control the pair to drop
 */
void nextPair(
	Field* field,
	int score,
	Position next2pair,
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1],
	MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1],
	MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]
);

/**
 * Drop the pair after the user press DOWN
 */
int fallPair(Field* field, MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]);

#endif
