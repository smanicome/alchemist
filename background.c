#include <MLV/MLV_all.h>
#include "background.h"
#include "data.h"

void drawPalet() {
	size_t i;
	MLV_Color* palet;
	palet = (MLV_Color*) malloc(11*sizeof(MLV_Color));
	getPalet(palet);
	for (i = MAX_LEVEL-1; i > 0; i--) {
		MLV_draw_filled_circle( 50, 50+(2*BALL_RADIUS+10)*(MAX_LEVEL-1-i), BALL_RADIUS, palet[i]);
	}
	free(palet);
}

void drawPanel() {
	MLV_draw_rectangle( WINDOW_WIDTH/4, WINDOW_HEIGHT/3, COL_COUNT*BALL_RADIUS*2+20, ROW_COUNT*BALL_RADIUS*2+20, MLV_COLOR_WHITE );
}

void drawBackground() {
	drawPalet();
	drawPanel();
	MLV_actualise_window();
}

void getPalet(MLV_Color* palet) {
	palet[0] = MLV_COLOR_BLACK;
	palet[1] = MLV_COLOR_GREEN;
	palet[2] = MLV_COLOR_ORANGE;
	palet[3] = MLV_COLOR_RED;
	palet[4] = MLV_COLOR_PURPLE;
	palet[5] = MLV_COLOR_BLUE1;
	palet[6] = MLV_COLOR_TURQUOISE;
	palet[7] = MLV_COLOR_GREEN3;
	palet[8] = MLV_COLOR_YELLOW;
	palet[9] = MLV_COLOR_GRAY;
	palet[10] = MLV_COLOR_WHITE;

	return;
}