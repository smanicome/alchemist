#ifndef ANIMATE_H_
#define ANIMATE_H_

#include <MLV/MLV_all.h>
#include "game.h"
#include "background.h"
#include "display.h"
#include "data.h"

/**
 * Load sprites to show while nothing is currently in work
 */
void loadStandingSprites(
	MLV_Image* images[MAX_LEVEL-1][STANDING_FRAMES],
	MLV_Animation* standing_animation[MAX_LEVEL-1],
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]
);

/**
 * Free memory allocated for sprites
 */
void freeStandingSprites(
	MLV_Image* images[MAX_LEVEL-1][STANDING_FRAMES],
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]
);

/**
 * Load sprites to show while a slime rolls
 */
void loadRollingSprites(
	MLV_Image* images[MAX_LEVEL-1][ROLLING_FRAMES],
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);
/**
 * Free memory allocated for sprites
 */
void freeRollingSprites(
	MLV_Image* images[MAX_LEVEL-1][ROLLING_FRAMES],
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);

/**
 * Load sprites to show while a slime jumps
 */
void loadJumpingSprites(
	MLV_Image* images[MAX_LEVEL-1][JUMPING_FRAMES],
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);
/**
 * Free memory allocated for sprites
 */
void freeJumpingSprites(
	MLV_Image* images[MAX_LEVEL-1][JUMPING_FRAMES],
	MLV_Animation* animation[MAX_LEVEL-1],
	MLV_Animation_player* animation_player[MAX_LEVEL-1]
);

/**
 * Display the frame of the animation of the standing slime
 * animation_player is the corresponding player
 * x is the actual horizontal position of the slime, relative to COL_COUNT
 * y is the actual vertical position of the slime, relative to ROW_COUNT
 */
void stand(MLV_Animation_player* animation_player, int x, int y);

/**
 * Display the frame of the animation of the rolling slime
 * animation_player is the corresponding player
 * x is the actual horizontal position of the slime, relative to COL_COUNT
 * y is the actual vertical position of the slime, relative to ROW_COUNT
 * distance is to be set if you want the animation to last more than the distance of a case, i.e. when the user drop a pair of slimes
 */
void rollDown(MLV_Animation_player* animation_player, int x, int y, int distance);

/**
 * Display the frame of the animation of the rolling slime
 * animation_player is the corresponding player, the player is played in reverse
 * x is the actual horizontal position of the slime, relative to COL_COUNT
 * y is the actual vertical position of the slime, relative to ROW_COUNT
 */
void rollUp(MLV_Animation_player* animation_player, int x, int y);

/**
 * Display the frame of the animation of the rolling slime
 * animation_player is the corresponding player, the player is played in reverse
 * x is the actual horizontal position of the slime, relative to COL_COUNT
 * y is the actual vertical position of the slime, relative to ROW_COUNT
 * direction is necessary to either jump left or right
 */
void slimeJump(MLV_Animation_player* animation_player, int x, int y, int direction);

#endif
