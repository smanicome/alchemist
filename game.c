#include <MLV/MLV_all.h>
#include <stdio.h>
#include <math.h>
#include "game.h"
#include "background.h"

void game() {
    int running = 1;
		int score;
    Field field;
    field.pos = malloc(sizeof(Position));
    initField(&field);

    while (running) {
        score = searchFuse(&field);
        generatePair(field.pos);
        updateScreen(&field, score);
        nextPair(&field, score);
        running = fallPair(&field);
        MLV_actualise_window();
    }

    free(field.pos);
}

void initField(Field* field) {
    size_t i;
    for ( i = 0; i < ROW_SIZE; i++) {
        size_t j;
        for ( j = 0; j < COL_SIZE; j++) {
            field->slots[i][j] = 0;
        }
    }
    return;
}

void generatePair(Position* pos) {
    pos->alignement = 2;
    pos->vertical = 0;
    pos->left_level=1;
    pos->right_level=1;
    pos->top_level=0;
    pos->bottom_level=0;
}

void updateScreen(Field* field, int score) {
    size_t i;
    size_t j;
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
        ROW_SIZE*BALL_RADIUS*2, 
        COL_SIZE*BALL_RADIUS*2, 
        MLV_COLOR_BLACK
    );
    
    /* Show field */
    for ( i = 0; i < ROW_SIZE; i++) {
        for ( j = 0; j < COL_SIZE; j++) {
            printf("%d ", field->slots[i][j]);
            MLV_draw_filled_circle( 
                i*BALL_RADIUS*2 + WINDOW_WIDTH/4+10 + BALL_RADIUS, 
                j*BALL_RADIUS*2 + WINDOW_HEIGHT/3+10 + BALL_RADIUS, 
                BALL_RADIUS,
                palet[field->slots[i][j]]
            );
        }
        putchar('\n');
    }
    putchar('\n');

    /* Clean next pair row */
    MLV_draw_filled_rectangle(
        WINDOW_WIDTH/4+10,
        WINDOW_HEIGHT/4 - 3*BALL_RADIUS, 
        ROW_SIZE*BALL_RADIUS*2+10, 
        4*BALL_RADIUS+10,
        MLV_COLOR_BLACK
    );

    /* Show next pair */
    if (field->pos->vertical) {
        MLV_draw_filled_circle( 
            field->pos->alignement * BALL_RADIUS * 2 + WINDOW_WIDTH/4+10 + BALL_RADIUS, 
            WINDOW_HEIGHT/4, 
            BALL_RADIUS, 
            palet[field->pos->bottom_level]
        );
        MLV_draw_filled_circle( 
            field->pos->alignement * BALL_RADIUS * 2 + WINDOW_WIDTH/4+10 + BALL_RADIUS, 
            WINDOW_HEIGHT/4 - BALL_RADIUS * 2, 
            BALL_RADIUS, 
            palet[field->pos->top_level]
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

		/* Clean next pair row */
    MLV_draw_filled_rectangle(
        5*WINDOW_WIDTH/6,
        WINDOW_HEIGHT/6, 
        100, 
        50,
        MLV_COLOR_BLACK
    );
		font = MLV_load_font( "font.ttf" , 50 );
		MLV_draw_text_with_font(5*WINDOW_WIDTH/6, WINDOW_HEIGHT/6, score_text, font, MLV_COLOR_WHITE);

    MLV_actualise_window();
    free(palet);
}

void nextPair(Field* field, int score) {
    MLV_Keyboard_button event;
    Position* pos = field->pos;

    MLV_wait_keyboard( &event, NULL, NULL );
    while (event != MLV_KEYBOARD_DOWN) {
        switch (event) {
        case MLV_KEYBOARD_UP:
            if (pos->vertical) {
                pos->left_level = pos->bottom_level;
                pos->bottom_level = 0;
                pos->right_level = pos->top_level;
                pos->top_level = 0;
    
                if (pos->alignement==ROW_SIZE-1) {
                    pos->alignement--;
                }
                
            } else {
                pos->top_level = pos->left_level;
                pos->left_level = 0;
                pos->bottom_level = pos->right_level;
                pos->right_level = 0;
            }
            pos->vertical = !(pos->vertical);
            break;
        case MLV_KEYBOARD_LEFT:
            if (pos->alignement > 0) {
                pos->alignement--;
            }            
            break;
        case MLV_KEYBOARD_RIGHT:
            if (pos->vertical && pos->alignement < 5) {
                pos->alignement++;
            } else if(!pos->vertical && pos->alignement < 4){
                pos->alignement++;
            }
            break;
        default:
            break;
        }
				updateScreen(field, score);
        MLV_wait_keyboard( &event, NULL, NULL );
    }
    return;
}

int fallPair(Field* field) {
    int still_running = 1;

    if (field->pos->vertical) {
        still_running = fillSlot(field->slots, field->pos->alignement, COL_SIZE-1, field->pos->bottom_level);
        still_running = fillSlot(field->slots, field->pos->alignement, COL_SIZE-1, field->pos->top_level);
    } else {
        still_running = fillSlot(field->slots, field->pos->alignement, COL_SIZE-1, field->pos->left_level);
        still_running = fillSlot(field->slots, field->pos->alignement+1, COL_SIZE-1, field->pos->right_level);
    }
    return still_running;
}

int fillSlot(int slots[ROW_SIZE][COL_SIZE], int alignement, int height, int elt) {
    if (height<0) {
        return 0;
    }

    if (!slots[alignement][height]) {
        slots[alignement][height] = elt;
        return 1;
    } else {
        return fillSlot(slots, alignement, height - 1, elt);
    }
}

int searchFuse(Field* field) {
    size_t i;
    size_t j;
		int x;
		int y;
		int fuse_to_process = 0;
		int path[ROW_SIZE][COL_SIZE] = {0};
    int score = 0;
		int length;

    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < COL_SIZE; j++) {
						if (path[i][j] || field->slots[i][j]==0) {
							continue;
						}
						
						x = ROW_SIZE;
						y = COL_SIZE;

            length = fusePath(field, i, j, path, &x, &y);
						if (length > 3) {
							score += pow(length, field->slots[i][j]);
							field->slots[x][y]++;
							fuse_to_process = 1;
						}
        }
    }

		if (fuse_to_process) {
			fuse(field, path);
			for (i = 0; i < ROW_SIZE; i++) {
        for (j = COL_SIZE-1; j >= 0; j--) {
					int tmp = field->slots[i][j];
					field->slots[i][j] = 0;

					fillSlot(field->slots, i, COL_SIZE-1, tmp);
				}
			}
			score += searchFuse(field);
		}
		
		return score;
}

int fusePath(Field* field, int x, int y, int path[ROW_SIZE][COL_SIZE], int* core_x, int* core_y) {
		
		int length = 1;
		path[x][y] = field->slots[x][y];

    if (x > 0) {
			if(field->slots[x][y] == field->slots[x-1][y] && !path[x-1][y]) {
				length += fusePath(field, x-1, y, path, core_x, core_y);
			}
		}

		if (y > 0 && field->slots[x][y] == field->slots[x][y-1] && !path[x][y-1]) {
			length += fusePath(field, x, y-1, path, core_x, core_y);
		}

		if (y < COL_SIZE-1 && field->slots[x][y] == field->slots[x][y+1] && !path[x][y+1]) {
			length += fusePath(field, x-1, y+1, path, core_x, core_y);
		}

		if (x < ROW_SIZE-1) {
			if(field->slots[x][y] == field->slots[x+1][y] && !path[x+1][y]) {
				length += fusePath(field, x+1, y, path, core_x, core_y);
			}
		}

		*core_x = x < *core_x ? x : *core_x;
		*core_y = y < *core_y ? y : *core_y;
		return length;
}

void fuse(Field* field, int path[ROW_SIZE][COL_SIZE]) {
	size_t i;
	size_t j;

	for (i = 0; i < ROW_SIZE; i++) {
		for (j = 0; j < COL_SIZE; j++) {
			if(field->slots[i][j] == path[i][j]) {
				field->slots[i][j] = 0;
			}
		}	
	}	
}