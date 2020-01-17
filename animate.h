#ifndef ANIMATE_H_
#define ANIMATE_H_

#include <MLV/MLV_all.h>
#include "game.h"
#include "background.h"
#include "display.h"
#include "data.h"

void loadStandingSprites(
	MLV_Image* images[MAX_LEVEL-1][STANDING_FRAMES], 
	MLV_Animation* standing_animation[MAX_LEVEL-1],
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]
);

void freeStandingSprites(
	MLV_Image* images[MAX_LEVEL-1][STANDING_FRAMES], 
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]
);

void loadRollingSprites(
	MLV_Image* images[MAX_LEVEL-1][ROLLING_FRAMES], 
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);
void freeRollingSprites(
	MLV_Image* images[MAX_LEVEL-1][ROLLING_FRAMES], 
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);

void loadJumpingSprites(
	MLV_Image* images[MAX_LEVEL-1][JUMPING_FRAMES], 
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);
void freeJumpingSprites(
	MLV_Image* images[MAX_LEVEL-1][JUMPING_FRAMES], 
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);

void stand(MLV_Animation_player* animation_player, int x, int y);

void rollDown(MLV_Animation_player* animation_player, int x, int y, int distance);

void rollUp(MLV_Animation_player* animation_player, int x, int y);

void slimeJump(MLV_Animation_player* animation_player, int x, int y, int direction);

#endif