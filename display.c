#include "display.h"

void updateScreen(Field* field, int score, Position next2pair, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]) {
	int i;
	
	for (i = 0; i < MAX_LEVEL-1; i++) {
		MLV_update_animation_player( standing_animation_player[i] );
	}

	cleanPalet();
	drawPalet(standing_animation_player);

	cleanField();
	showField(field, standing_animation_player);
	
	cleanNextPairRow();
	showNextPair(field, standing_animation_player);

	cleanScoreRow();
	showScore(score);
	
	cleanNext2PairRow();
	showNext2Pair(next2pair, standing_animation_player);

	MLV_actualise_window();
}


void cleanField() {
	MLV_draw_filled_rectangle(
		WINDOW_WIDTH/4+10,
		WINDOW_HEIGHT/3+10,
		COL_COUNT*SLIME_SIZE,
		ROW_COUNT*SLIME_SIZE,
		MLV_COLOR_BLACK
	);
}

void showField(Field* field, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]) {
	int i;
	int j;

	for ( i = 0; i < ROW_COUNT; i++) {
		for ( j = 0; j < COL_COUNT; j++) {
			if (field->slots[i][j] != 0) {
				stand( 
					standing_animation_player[ field->slots[i][j]-1 ],
					j*SLIME_SIZE + WINDOW_WIDTH/4+10, 
					i*SLIME_SIZE + WINDOW_HEIGHT/3+10
				);
			}
		}
	}
}

void cleanNextPairRow() {
	MLV_draw_filled_rectangle(
		WINDOW_WIDTH/4+10,
		WINDOW_HEIGHT/4 - SLIME_SIZE,
		COL_COUNT*SLIME_SIZE,
		2*SLIME_SIZE,
		MLV_COLOR_BLACK
	);
}

void showNextPair(Field* field, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]) {
	if (field->pos->vertical) {
		stand( 
			standing_animation_player[ field->pos->left_level-1 ],
			field->pos->alignement * SLIME_SIZE + WINDOW_WIDTH/4+10, 
			WINDOW_HEIGHT/3 - 2*SLIME_SIZE
		);
		stand( 
			standing_animation_player[ field->pos->right_level-1 ],
			field->pos->alignement * SLIME_SIZE + WINDOW_WIDTH/4+10, 
			WINDOW_HEIGHT/3 - SLIME_SIZE
		);
	} else {
		stand( 
			standing_animation_player[ field->pos->left_level-1 ],
			field->pos->alignement * SLIME_SIZE + WINDOW_WIDTH/4+10, 
			WINDOW_HEIGHT/3 - SLIME_SIZE
		);
		stand( 
			standing_animation_player[ field->pos->right_level-1 ],
			field->pos->alignement * SLIME_SIZE + WINDOW_WIDTH/4+10 + SLIME_SIZE, 
			WINDOW_HEIGHT/3 - SLIME_SIZE
		);
	}
}

void cleanScoreRow() {
	MLV_draw_filled_rectangle(
		5*WINDOW_WIDTH/6,
		WINDOW_HEIGHT/6,
		WINDOW_WIDTH/6,
		50,
		MLV_COLOR_BLACK
	);
}

void showScore(int score) {
	MLV_Font* font;
	char score_text[100];
	sprintf(score_text, "%d", score);

	font = MLV_load_font( "font.ttf" , 50 );
	MLV_draw_text_with_font(5*WINDOW_WIDTH/6, WINDOW_HEIGHT/6, score_text, font, MLV_COLOR_WHITE);
	MLV_free_font(font);
}

void cleanNext2PairRow() {
	MLV_draw_filled_rectangle(
		5*WINDOW_WIDTH/6,
		WINDOW_HEIGHT/3,
		2*SLIME_SIZE,
		2*SLIME_SIZE,
		MLV_COLOR_BLACK
	);
}

/**
 * Display the following pair to drop on the right side
 */
void showNext2Pair(Position next2pair, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]) {
	stand( 
		standing_animation_player[ next2pair.left_level-1 ], 
		5*WINDOW_WIDTH/6, 
		WINDOW_HEIGHT/3
	);
	stand( 
		standing_animation_player[ next2pair.right_level-1 ], 
		SLIME_SIZE + 5*WINDOW_WIDTH/6, 
		WINDOW_HEIGHT/3
	);
}