#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "background.h"
#include "peer.h"

void game() {
	int running = 1;
	int score = 0;
	int available_level[MAX_LEVEL] = {0};
	Position next2peer;
	Field field;

	available_level[1] = 1;
	field.pos = malloc(sizeof(Position));
	initField(&field, &next2peer);
	generatePeer(field.pos, available_level);

	while (running) {
		generatePeer(&next2peer, available_level);
		updateScreen(&field, score, next2peer);
		nextPeer(&field, score, next2peer);
		running = fallPeer(&field);
		updateScreen(&field, score, next2peer);
		score += searchFuse(&field, available_level);

		field.pos->left_level = next2peer.left_level;
		field.pos->right_level = next2peer.right_level;
	}

	free(field.pos);
}

void initField(Field* field, Position* next2peer) {
	int i;

	field->pos->left_level = 0;
	field->pos->right_level = 0;
	field->pos->alignement = 2;
	field->pos->vertical = 0;

	next2peer->left_level = 0;
	next2peer->right_level = 0;
	next2peer->alignement = 2;
	next2peer->vertical = 0;

	for ( i = 0; i < ROW_COUNT; i++) {
		int j;
		for ( j = 0; j < COL_COUNT; j++) {
			field->slots[i][j] = 0;
		}
	}
	return;
}

void updateScreen(Field* field, int score, Position next2peer) {
	int i;
	int j;
	MLV_Color* palet;
	MLV_Font* font;
	char score_text[100];
	sprintf(score_text, "%d", score);
	palet = (MLV_Color*) malloc(11*sizeof(MLV_Color));
	getPalet(palet);

	/* Clean field */
	MLV_draw_filled_rectangle(
		WINDOW_WIDTH/4+10,
		WINDOW_HEIGHT/3+10,
		COL_COUNT*BALL_RADIUS*2,
		ROW_COUNT*BALL_RADIUS*2,
		MLV_COLOR_BLACK
	);

	/* Show field */
	for ( i = 0; i < COL_COUNT; i++) {
		for ( j = 0; j < ROW_COUNT; j++) {
			MLV_draw_filled_circle(
				i*BALL_RADIUS*2 + WINDOW_WIDTH/4+10 + BALL_RADIUS,
				j*BALL_RADIUS*2 + WINDOW_HEIGHT/3+10 + BALL_RADIUS,
				BALL_RADIUS,
				palet[field->slots[j][i]]
			);
		}
	}

	/* Clean next peer row */
	MLV_draw_filled_rectangle(
		WINDOW_WIDTH/4+10,
		WINDOW_HEIGHT/4 - 3*BALL_RADIUS,
		COL_COUNT*BALL_RADIUS*2+10,
		4*BALL_RADIUS+10,
		MLV_COLOR_BLACK
	);

	/* Show next peer */
	if (field->pos->vertical) {
		MLV_draw_filled_circle(
			field->pos->alignement * BALL_RADIUS * 2 + WINDOW_WIDTH/4+10 + BALL_RADIUS,
			WINDOW_HEIGHT/4 - BALL_RADIUS * 2,
			BALL_RADIUS,
			palet[field->pos->left_level]
		);
		MLV_draw_filled_circle(
			field->pos->alignement * BALL_RADIUS * 2 + WINDOW_WIDTH/4+10 + BALL_RADIUS,
			WINDOW_HEIGHT/4,
			BALL_RADIUS,
			palet[field->pos->right_level]
		);
	} else {
		MLV_draw_filled_circle(
			field->pos->alignement * BALL_RADIUS * 2 + WINDOW_WIDTH/4+10 + BALL_RADIUS,
			WINDOW_HEIGHT/4,
			BALL_RADIUS,
			palet[field->pos->left_level]
		);
		MLV_draw_filled_circle(
			(field->pos->alignement+1) * BALL_RADIUS * 2 + WINDOW_WIDTH/4+10 + BALL_RADIUS,
			WINDOW_HEIGHT/4,
			BALL_RADIUS,
			palet[field->pos->right_level]
		);
	}

	/* Clean score row */
	MLV_draw_filled_rectangle(
		5*WINDOW_WIDTH/6,
		WINDOW_HEIGHT/6,
		WINDOW_WIDTH/6,
		50,
		MLV_COLOR_BLACK
	);

	/* Show score row */
	font = MLV_load_font( "font.ttf" , 50 );
	MLV_draw_text_with_font(5*WINDOW_WIDTH/6, WINDOW_HEIGHT/6, score_text, font, MLV_COLOR_WHITE);

	/* Clean next2peer row */
	MLV_draw_filled_rectangle(
		5*WINDOW_WIDTH/6,
		WINDOW_HEIGHT/3,
		4*BALL_RADIUS+10,
		4*BALL_RADIUS+10,
		MLV_COLOR_BLACK
	);

	/* Show next2peer */
	if (next2peer.vertical) {
		MLV_draw_filled_circle(
			5*WINDOW_WIDTH/6 + BALL_RADIUS,
			WINDOW_HEIGHT/3,
			BALL_RADIUS,
			palet[next2peer.left_level]
		);
		MLV_draw_filled_circle(
			5*WINDOW_WIDTH/6 + BALL_RADIUS,
			WINDOW_HEIGHT/3 + BALL_RADIUS * 2,
			BALL_RADIUS,
			palet[next2peer.right_level]
		);
	} else {
		MLV_draw_filled_circle(
			5*WINDOW_WIDTH/6 + BALL_RADIUS,
			WINDOW_HEIGHT/3,
			BALL_RADIUS,
			palet[next2peer.left_level]
		);
		MLV_draw_filled_circle(
			BALL_RADIUS*2 + 5*WINDOW_WIDTH/6 + BALL_RADIUS,
			WINDOW_HEIGHT/3,
			BALL_RADIUS,
			palet[next2peer.right_level]
		);
	}

	MLV_actualise_window();
	free(palet);
}





int fillSlot(int slots[ROW_COUNT][COL_COUNT], int alignement, int height, int elt) {
	if (height<0) {
		return 0;
	}

	if (!slots[height][alignement]) {
		slots[height][alignement] = elt;
		return 1;
	} else {
		return fillSlot(slots, alignement, height - 1, elt);
	}
}

int searchFuse(Field* field, int available_level[MAX_LEVEL]) {
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

				if (field->slots[i][j] < MAX_LEVEL-1) {
					available_level[ field->slots[i][j] ] = 1;
				}
				
				score += pow(length, field->slots[i][j]);
				fuse(field, i, j, path, DOWN);
				field->slots[i][j] = (tmp+1)%MAX_LEVEL;

				fall_to_process = 1;
			}
		}
	}

	/* fuse all at once */
	if (fall_to_process) {
		for (i = ROW_COUNT-2; i>=0; i--) {
			for (j = 0; j < COL_COUNT; j++) {
				int tmp = field->slots[i][j];
				if (tmp!=0) {
					field->slots[i][j] = 0;
					fillSlot(field->slots, j, ROW_COUNT-1, tmp);
				}
			}
		}
		score += searchFuse(field, available_level);
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

void fuse(Field* field, int x, int y, int path[ROW_COUNT][COL_COUNT], int direction) {
	/* check top ball */
	if (x > 0) {
		if(path[x-1][y]) {
			path[x-1][y] = 0;
			fuse(field, x-1, y, path, DOWN);
		}
	}

	/* check left ball */
	if (y > 0) {
		if(path[x][y-1]) {
			path[x][y-1] = 0;
			fuse(field, x, y-1, path, RIGHT);
		}
	}

	/* check right ball */
	if (y < COL_COUNT-1) {
		if(path[x][y+1]) {
			path[x][y+1] = 0;
			fuse(field, x, y+1, path, LEFT);
		}
	}

	/* check bottom ball */
	if (x < ROW_COUNT-1) {
		if(path[x+1][y]) {
			path[x+1][y] = 0;
			fuse(field, x+1, y, path, UP);
		}
	}

	field->slots[x][y] = 0;
}