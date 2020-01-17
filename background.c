#include "background.h"

void drawPalet(MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]) {
	size_t i;

	for (i = 0; i < MAX_LEVEL-1; i++) {
		stand( 
			standing_animation_player[ i ], 
			50, 
			50+(SLIME_SIZE+10)*(MAX_LEVEL-1-i)
		);
	}
}

void cleanPalet() {
	MLV_draw_filled_rectangle( 50, 0, SLIME_SIZE, WINDOW_HEIGHT, MLV_COLOR_BLACK);
}

void drawPanel() {
	MLV_draw_rectangle( WINDOW_WIDTH/4, WINDOW_HEIGHT/3, COL_COUNT*SLIME_SIZE+20, ROW_COUNT*SLIME_SIZE+20, MLV_COLOR_WHITE );
}

void cleanPanel() {
	MLV_draw_rectangle( WINDOW_WIDTH/4, WINDOW_HEIGHT/3, COL_COUNT*SLIME_SIZE+20, ROW_COUNT*SLIME_SIZE+20, MLV_COLOR_BLACK );
}

void drawBackground(MLV_Animation_player* standing_animation_player[MAX_LEVEL-1]) {
	drawPalet(standing_animation_player);
	drawPanel();
	MLV_actualise_window();
}