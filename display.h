#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <MLV/MLV_all.h>
#include "data.h"
#include "background.h"
#include "animate.h"

void updateScreen(Field* field, int score, Position next2pair, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

/**
 * Used to clean filled before updating display
 */
void cleanField();

/**
 * Display slimes in field
 */
void showField(Field* field, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

void cleanNextPairRow();

/**
 * Display next pair to drop above the field
 */
void showNextPair(Field* field, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

void cleanScoreRow();

/**
 * Display score on the right side
 */
void showScore(int score);

void cleanNext2PairRow();

/**
 * Display the following pair to drop on the right side
 */
void showNext2Pair(Position next2pair, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

#endif