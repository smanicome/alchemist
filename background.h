#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <MLV/MLV_all.h>
#include "data.h"
#include "animate.h"

/**
 * Show all animated slimes
 */
void drawPalet(MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

void cleanPalet();

/**
 * Show the frame in which the slimes are contained
 */
void drawPanel();

void cleanPanel();

/**
 * Call drawPalet and drawPanel
 */
void drawBackground(MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

#endif
