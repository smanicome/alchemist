#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <MLV/MLV_all.h>
#include "data.h"
#include "animate.h"

void drawPalet(MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

void cleanPalet();

void drawPanel();

void cleanPanel();

void drawBackground(MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]);

#endif