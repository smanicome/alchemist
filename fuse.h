#ifndef FUSE_H_
#define FUSE_H_

#include <MLV/MLV_all.h>
#include "game.h"
#include "data.h"

/**
 * Searches in a layer of the board all the path to fuse
 * Recursive calls
 */
int searchFuse(
	Field* field,
	int available_level[MAX_LEVEL],
	MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1],
	MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1]
);

/**
 * Checks if the given path is long enough
 * Recursive calls
 */
int fusePath(
	Field* field,
	int x,
	int y,
	int path[ROW_COUNT][COL_COUNT],
	int length
);

/**
 * Fuse the slimes, display animation and empty the board
 * Recursive calls
 */
void fuse(
	Field* field,
	int x,
	int y,
	int path[ROW_COUNT][COL_COUNT],
	int direction,
	MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1],
	MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1]
);


#endif
