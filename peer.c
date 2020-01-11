#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>
#include "game.h"
#include "background.h"

void generatePeer(Position* pos, int available_level[MAX_LEVEL]) {
	int availables = 0;
	size_t i;

	/* You cannot generate a black ball nor max ball */
	for (i = 1; i < MAX_LEVEL-1; i++) {
		availables += available_level[i];
	}
	
	srand(time(NULL));
	pos->left_level = (rand()%availables)+1;
	pos->right_level = (rand()%availables)+1;
}

void nextPeer(Field* field, int score, Position next2peer) {
	MLV_Keyboard_button event;
	Position* pos = field->pos;

	MLV_wait_keyboard( &event, NULL, NULL );
	while (event != MLV_KEYBOARD_DOWN) {
		switch (event) {
		case MLV_KEYBOARD_UP:
			if (pos->vertical) {
				int tmp;

				tmp = pos->left_level;
				pos->left_level = pos->right_level;
				pos->right_level = tmp;

				if (pos->alignement==ROW_COUNT-1) {
					pos->alignement--;
				}

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
		updateScreen(field, score, next2peer);
		MLV_wait_keyboard( &event, NULL, NULL );
	}
	return;
}

int fallPeer(Field* field) {
		int still_running = 1;

		if (field->pos->vertical) {
			still_running = fillSlot(field->slots, field->pos->alignement, ROW_COUNT-1, field->pos->right_level);
			still_running = fillSlot(field->slots, field->pos->alignement, ROW_COUNT-1, field->pos->left_level);
		} else {
			still_running = fillSlot(field->slots, field->pos->alignement, ROW_COUNT-1, field->pos->left_level);
			still_running = fillSlot(field->slots, field->pos->alignement+1, ROW_COUNT-1, field->pos->right_level);
		}
		
		return still_running;
}