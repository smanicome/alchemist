#include "pair.h"

void generatePair(Position* pos, int available_level[MAX_LEVEL]) {
	int availables = 0;
	size_t i;

	/* You cannot generate a black ball nor a max ball */
	for (i = 1; i < MAX_LEVEL-1; i++) {
		availables += available_level[i];
	}

	srand(time(NULL));
	pos->left_level = (rand()%availables)+1;
	pos->right_level = (rand()%availables)+1;
}

void nextPair(Field* field, int score, Position next2pair, MLV_Animation_player* standing_animation_player[MAX_LEVEL-1], MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1], MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]) {
	Position* pos = field->pos;
	int single_press = 1;

	while ( MLV_get_keyboard_state( MLV_KEYBOARD_DOWN ) != MLV_PRESSED ) {

		if(single_press) {
			if ( MLV_get_keyboard_state( MLV_KEYBOARD_UP ) == MLV_PRESSED ){
				if (pos->vertical) {
					int tmp;

					if (pos->alignement==COL_COUNT-1) {
            slimeJump(jumping_animation_player[pos->right_level - 1], pos->alignement, -1, LEFT);
            pos->alignement--;
          } else {
            slimeJump(jumping_animation_player[pos->left_level - 1], pos->alignement, -2, RIGHT);
          }

          rollDown(rolling_animation_player[pos->left_level - 1], pos->alignement + 1, -2, 1);

          tmp = pos->left_level;
          pos->left_level = pos->right_level;
          pos->right_level = tmp;

        } else {
					rollUp( rolling_animation_player[ pos->left_level-1 ], pos->alignement, -1 );
					slimeJump( jumping_animation_player[ pos->right_level-1 ], pos->alignement+1, -1, LEFT );

				}
				pos->vertical = !(pos->vertical);
				single_press = 0;
			}

			if ( MLV_get_keyboard_state( MLV_KEYBOARD_LEFT ) == MLV_PRESSED ) {
				if (pos->alignement > 0) {
					slimeJump(jumping_animation_player[ pos->left_level-1 ], pos->alignement, -1 - pos->vertical, LEFT);
					slimeJump(jumping_animation_player[ pos->right_level-1 ], pos->alignement + 1 - pos->vertical, -1, LEFT);
					pos->alignement--;
				}
				single_press = 0;
			}

			if ( MLV_get_keyboard_state( MLV_KEYBOARD_RIGHT ) == MLV_PRESSED ) {
				if (pos->vertical && pos->alignement < 5) {

					slimeJump(jumping_animation_player[ pos->right_level-1 ], pos->alignement, -1, RIGHT);
					slimeJump(jumping_animation_player[ pos->left_level-1 ], pos->alignement, -2, RIGHT);
					pos->alignement++;

				} else if(!pos->vertical && pos->alignement < 4){

					slimeJump(jumping_animation_player[ pos->right_level-1 ], pos->alignement + 1, -1, RIGHT);
					slimeJump(jumping_animation_player[ pos->left_level-1 ], pos->alignement, -1, RIGHT);
					pos->alignement++;

				}
				single_press = 0;
			}
		}

		if (
			MLV_get_keyboard_state( MLV_KEYBOARD_UP ) == MLV_RELEASED &&
			MLV_get_keyboard_state( MLV_KEYBOARD_LEFT ) == MLV_RELEASED &&
			MLV_get_keyboard_state( MLV_KEYBOARD_RIGHT ) == MLV_RELEASED
		) {
			single_press = 1;
		}

		updateScreen(field, score, next2pair, standing_animation_player);
		MLV_delay_according_to_frame_rate();
	}

	while(MLV_get_keyboard_state( MLV_KEYBOARD_DOWN ) != MLV_RELEASED){}

	return;
}

int fallPair(Field* field, MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]) {
		int still_running = 1;

		if (field->pos->vertical) {
			still_running = fillSlot(field->slots, field->pos->alignement, -1, ROW_COUNT-1, field->pos->right_level, rolling_animation_player);
			still_running = fillSlot(field->slots, field->pos->alignement, -2, ROW_COUNT-1, field->pos->left_level, rolling_animation_player);
		} else {
			still_running = fillSlot(field->slots, field->pos->alignement, -1, ROW_COUNT-1, field->pos->left_level, rolling_animation_player);
			still_running = fillSlot(field->slots, field->pos->alignement+1, -1, ROW_COUNT-1, field->pos->right_level, rolling_animation_player);
		}

		return still_running;
}
