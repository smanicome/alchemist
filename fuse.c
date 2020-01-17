#include "fuse.h"

int searchFuse(Field* field, int available_level[MAX_LEVEL], MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1], MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1]) {
	int i;
	int j;
	int fall_to_process = 0;
	int score = 0;
	int length;

	for (i = ROW_COUNT-1; i >= 0; i--) {
		for (j = 0; j < COL_COUNT; j++) {
			int path[ROW_COUNT][COL_COUNT] = {0};

			if (field->slots[i][j]==0) {
				continue;
			}

			length = fusePath(field, i, j, path, 1);

			if (length >= 3) {
				int tmp;
				tmp = field->slots[i][j];

				/* add the result color to the list of available colors */
				if (field->slots[i][j] < MAX_LEVEL-1) {
					available_level[ field->slots[i][j] ] = 1;
				}
				
				score += pow(length, field->slots[i][j]);
				fuse(field, i, j, path, NONE, rolling_animation_player, jumping_animation_player);
				field->slots[i][j] = (tmp+1) % MAX_LEVEL;

				fall_to_process = 1;
			}
		}
	}

	if (fall_to_process) {
		for (i = ROW_COUNT-2; i>=0; i--) {
			for (j = 0; j < COL_COUNT; j++) {
				int tmp = field->slots[i][j];
				if (tmp!=0) {
					field->slots[i][j] = 0;
					fillSlot(field->slots, j, i, ROW_COUNT-1, tmp, rolling_animation_player);
				}
			}
		}
		score += searchFuse(field, available_level, rolling_animation_player, jumping_animation_player);
	}

	return score;
}

int fusePath(Field* field, int x, int y, int path[ROW_COUNT][COL_COUNT], int length) {
	int sum_branch = 1;
	path[x][y] = field->slots[x][y];

	/* check top ball */
	if (x > 0) {
		if(field->slots[x][y] == field->slots[x-1][y] && !path[x-1][y]) {
			sum_branch += fusePath(field, x-1, y, path, length+1);
		}
	}

	/* check left ball */
	if (y > 0) {
		if(field->slots[x][y] == field->slots[x][y-1] && !path[x][y-1]) {
			sum_branch += fusePath(field, x, y-1, path, length+1);
		}
	}

	/* check right ball */
	if (y < COL_COUNT-1) {
		if(field->slots[x][y] == field->slots[x][y+1] && !path[x][y+1]) {
			sum_branch += fusePath(field, x, y+1, path, length+1);
		}
	}

	/* check bottom ball */
	if (x < ROW_COUNT-1) {
		if(field->slots[x][y] == field->slots[x+1][y] && !path[x+1][y]) {
			sum_branch += fusePath(field, x+1, y, path, length+1);
		}
	}
	return sum_branch;
}

void fuse(Field* field, int x, int y, int path[ROW_COUNT][COL_COUNT], int direction, MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1], MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1]) {
	path[x][y] = 0;
	
	/* check top ball */
	if (x > 0) {
		if(path[x-1][y]) {
			fuse(field, x-1, y, path, DOWN, rolling_animation_player, jumping_animation_player);
		}
	}

	/* check left ball */
	if (y > 0) {
		if(path[x][y-1]) {
			fuse(field, x, y-1, path, RIGHT, rolling_animation_player, jumping_animation_player);
		}
	}

	/* check right ball */
	if (y < COL_COUNT-1) {
		if(path[x][y+1]) {
			fuse(field, x, y+1, path, LEFT, rolling_animation_player, jumping_animation_player);
		}
	}

	/* check bottom ball */
	if (x < ROW_COUNT-1) {
		if(path[x+1][y]) {
			fuse(field, x+1, y, path, UP, rolling_animation_player, jumping_animation_player);
		}
	}

	if( direction != NONE ) {
		if ( direction == DOWN ) {
			rollDown(
				rolling_animation_player[ field->slots[x][y]-1 ],
				y,
				x,
				1
			);
		} else if ( direction == UP ) {
			rollUp(
				rolling_animation_player[ field->slots[x][y]-1 ],
				y,
				x
			);
		} else if( direction == LEFT || direction == RIGHT ) {
			slimeJump( jumping_animation_player[ field->slots[x][y]-1 ], y, x, direction );
		}
	}
	field->slots[x][y] = 0;
}

