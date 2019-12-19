#include <MLV/MLV_all.h>
#include "background.h"
#include "data.h"


void drawPalet() {
    size_t i;

    MLV_Color palet[10];
    palet[0] = MLV_COLOR_WHITE;
    palet[1] = MLV_COLOR_GRAY;
    palet[2] = MLV_COLOR_YELLOW;
    palet[3] = MLV_COLOR_GREEN3;
    palet[4] = MLV_COLOR_TURQUOISE;
    palet[5] = MLV_COLOR_BLUE1;
    palet[6] = MLV_COLOR_PURPLE;
    palet[7] = MLV_COLOR_RED;
    palet[8] = MLV_COLOR_ORANGE;
    palet[9] = MLV_COLOR_GREEN;

    for (i = 0; i < 10; i++) {
        MLV_draw_filled_circle( 50, 50+(2*BALL_RADIUS+10)*i, BALL_RADIUS, palet[i]);
    }
}

void drawPanel() {
    MLV_draw_rectangle( 500, 500, 6*BALL_RADIUS*2, 8*BALL_RADIUS*2, MLV_COLOR_WHITE );
}

void drawBackground() {
    drawPalet();
    drawPanel();
    MLV_actualise_window();
}