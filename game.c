#include "game.h"

void game() {
	int running = 1;
	int score = 0;
	int available_level[MAX_LEVEL] = {0};
	Position next2pair;
	Field field;
	MLV_Music* music;

	/* declare standing animations */
	MLV_Image* standing_sprites[MAX_LEVEL-1][STANDING_FRAMES];
	MLV_Animation* standing_animation[MAX_LEVEL-1];
	MLV_Animation_player* standing_animation_player[MAX_LEVEL-1];

	/* declare rolling animations */
	MLV_Image* rolling_sprites[MAX_LEVEL-1][ROLLING_FRAMES];
	MLV_Animation* rolling_animation[MAX_LEVEL-1];
	MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1];

	/* declare jumping animations */
	MLV_Image* jumping_sprites[MAX_LEVEL-1][JUMPING_FRAMES];
	MLV_Animation* jumping_animation[MAX_LEVEL-1];
	MLV_Animation_player* jumping_animation_player[MAX_LEVEL-1];

	/* launch weird and (maybe) funny music */
	MLV_init_audio( );
	music = MLV_load_music( "assets/off_limits.wav" );
	MLV_play_music( music, 1.0, -1 );

	/* load animations */
	loadStandingSprites(standing_sprites, standing_animation, standing_animation_player);
	loadRollingSprites(rolling_sprites, rolling_animation, rolling_animation_player);
	loadJumpingSprites(jumping_sprites, jumping_animation, jumping_animation_player);

	drawBackground(standing_animation_player);

	available_level[1] = 1;
	field.pos = malloc(sizeof(Position));

	initField(&field, &next2pair);
	generatePair(field.pos, available_level);

	while (running) {

		generatePair(&next2pair, available_level);

		updateScreen(&field, score, next2pair, standing_animation_player);

		nextPair(&field, score, next2pair, standing_animation_player, jumping_animation_player, rolling_animation_player);

		running = fallPair(&field, rolling_animation_player);

		updateScreen(&field, score, next2pair, standing_animation_player);

		score += searchFuse(&field, available_level, rolling_animation_player, jumping_animation_player);

		field.pos->left_level = next2pair.left_level;
		field.pos->right_level = next2pair.right_level;
	}

	free(field.pos);
	freeStandingSprites(standing_sprites, standing_animation, standing_animation_player);
	freeRollingSprites(rolling_sprites, rolling_animation, rolling_animation_player);
	freeJumpingSprites(jumping_sprites, jumping_animation, jumping_animation_player);
	MLV_stop_music();
	MLV_free_music( music );
}

void initField(Field* field, Position* next2pair) {
	int i;

	field->pos->left_level = 0;
	field->pos->right_level = 0;
	field->pos->alignement = 2;
	field->pos->vertical = 0;

	next2pair->left_level = 0;
	next2pair->right_level = 0;
	next2pair->alignement = 2;
	next2pair->vertical = 0;

	for ( i = 0; i < ROW_COUNT; i++) {
		int j;
		for ( j = 0; j < COL_COUNT; j++) {
			field->slots[i][j] = 0;
		}
	}
	return;
}

int fillSlot(int slots[ROW_COUNT][COL_COUNT], int alignement, int previous_height, int height, int elt, MLV_Animation_player* rolling_animation_player[MAX_LEVEL-1]) {

	if (height<0) {
		return 0;
	}

	if (!slots[height][alignement]) {
		slots[height][alignement] = elt;

		rollDown(rolling_animation_player[ elt-1 ], alignement, previous_height, (height-previous_height));
		
		return 1;

	} else {
		return fillSlot(slots, alignement, previous_height, height - 1, elt, rolling_animation_player);
	}
}