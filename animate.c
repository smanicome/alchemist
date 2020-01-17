#include "animate.h"

void loadStandingSprites(MLV_Image* images[MAX_LEVEL-1][STANDING_FRAMES], MLV_Animation* animation[MAX_LEVEL-1], MLV_Animation_player* animation_player[MAX_LEVEL-1]) {
	size_t i;
	size_t j;

	char file_path_of_slime[50];

	for (i = 0; i < MAX_LEVEL-1; i++) {
		MLV_Image* slime;
		int w, h;
		w = SLIME_SIZE;
		h = SLIME_SIZE;
		
		sprintf(file_path_of_slime, "%s%ld%s","assets/standing_slime", i, ".png");
		slime =  MLV_load_image( file_path_of_slime );

		if( ! slime ){
			fprintf(
				stderr, "It was impossible to load the file %s.\n",
				file_path_of_slime
			);
			exit(1);
		}

		animation[i] = MLV_create_animation(STANDING_FRAMES, 1, 0);

		for (j = 0; j < STANDING_FRAMES; j++) {
			images[i][j] = MLV_copy_partial_image( slime, 0+j*w, 0, w, h );
			MLV_add_frame_in_animation( images[i]+j, NULL, 10, animation[i] );
		}

		MLV_free_image(slime);

		animation_player[i] = MLV_create_animation_player( animation[i] );
		MLV_play_animation_player( animation_player [i] );
	}
}

void freeStandingSprites(MLV_Image* images[MAX_LEVEL-1][STANDING_FRAMES], MLV_Animation* animation[MAX_LEVEL-1], MLV_Animation_player* animation_player[MAX_LEVEL-1]) {
	size_t i;
	size_t j;

	for (i = 0; i < MAX_LEVEL-1; i++) {
		free(animation_player[i]);
		free(animation[i]);
		for (j = 0; j < STANDING_FRAMES; j++) {
			MLV_free_image(images[i][j]);
		}
	}
}

void loadRollingSprites(MLV_Image* images[MAX_LEVEL-1][ROLLING_FRAMES], MLV_Animation* animation[MAX_LEVEL-1], MLV_Animation_player* animation_player[MAX_LEVEL-1]) {
	size_t i;
	size_t j;

	char file_path_of_slime[50];

	for (i = 0; i < MAX_LEVEL-1; i++) {
		MLV_Image* slime;
		int w, h;
		w = SLIME_SIZE;
		h = SLIME_SIZE;
		
		sprintf(file_path_of_slime, "%s%ld%s","assets/rolling_slime", i, ".png");
		slime =  MLV_load_image( file_path_of_slime );

		if( ! slime ){
			fprintf(
				stderr, "It was impossible to load the file %s.\n",
				file_path_of_slime
			);
			exit(1);
		}

		animation[i] = MLV_create_animation(ROLLING_FRAMES, 1, 0);

		for (j = 0; j < ROLLING_FRAMES; j++) {
			images[i][j] = MLV_copy_partial_image( slime, 0+j*w, 0, w, h );
			MLV_add_frame_in_animation( images[i]+j, NULL, 10, animation[i] );
		}

		MLV_free_image(slime);

		animation_player[i] = MLV_create_animation_player( animation[i] );
	}
}

void freeRollingSprites(MLV_Image* images[MAX_LEVEL-1][ROLLING_FRAMES], MLV_Animation* animation[MAX_LEVEL-1], MLV_Animation_player* animation_player[MAX_LEVEL-1]) {
	size_t i;
	size_t j;

	for (i = 0; i < MAX_LEVEL-1; i++) {
		free(animation_player[i]);
		free(animation[i]);
		for (j = 0; j < ROLLING_FRAMES; j++) {
			MLV_free_image(images[i][j]);
		}
	}
}

void loadJumpingSprites(MLV_Image* images[MAX_LEVEL-1][JUMPING_FRAMES], MLV_Animation* animation[MAX_LEVEL-1], MLV_Animation_player* animation_player[MAX_LEVEL-1]) {
	size_t i;
	size_t j;

	char file_path_of_slime[50];

	for (i = 0; i < MAX_LEVEL-1; i++) {
		MLV_Image* slime;
		int w, h;
		w = SLIME_SIZE;
		h = SLIME_SIZE;
		
		sprintf(file_path_of_slime, "%s%ld%s","assets/jumping_slime", i, ".png");
		slime =  MLV_load_image( file_path_of_slime );

		if( ! slime ){
			fprintf(
				stderr, "It was impossible to load the file %s.\n",
				file_path_of_slime
			);
			exit(1);
		}

		animation[i] = MLV_create_animation(JUMPING_FRAMES, 1, 0);

		for (j = 0; j < JUMPING_FRAMES; j++) {
			images[i][j] = MLV_copy_partial_image( slime, 0+j*w, 0, w, h );
			MLV_add_frame_in_animation( images[i]+j, NULL, 10, animation[i] );
		}

		MLV_free_image(slime);

		animation_player[i] = MLV_create_animation_player( animation[i] );
		MLV_play_animation_player( animation_player [i] );
	}
}

void freeJumpingSprites(MLV_Image* images[MAX_LEVEL-1][JUMPING_FRAMES], MLV_Animation* animation[MAX_LEVEL-1], MLV_Animation_player* animation_player[MAX_LEVEL-1]) {
	size_t i;
	size_t j;

	for (i = 0; i < MAX_LEVEL-1; i++) {
		free(animation_player[i]);
		free(animation[i]);
		for (j = 0; j < JUMPING_FRAMES; j++) {
			MLV_free_image(images[i][j]);
		}
	}
}

void stand(MLV_Animation_player* animation_player, int x, int y) {
	MLV_draw_image_from_animation_player( animation_player, 0, x, y );
}

void rollDown(MLV_Animation_player* animation_player, int x, int y, int distance) {
	int i;

	MLV_play_animation_player( animation_player );

	for (i = 0; i < distance*SLIME_SIZE; i = i+4) {
		MLV_draw_filled_rectangle(
			x*SLIME_SIZE + WINDOW_WIDTH/4+10,
			i + y*SLIME_SIZE + WINDOW_HEIGHT/3+10,
			SLIME_SIZE,
			SLIME_SIZE,
			MLV_COLOR_BLACK
		);

		MLV_draw_image_from_animation_player( 
			animation_player, 
			0, 
			x*SLIME_SIZE + WINDOW_WIDTH/4+10,
			i + y*SLIME_SIZE + WINDOW_HEIGHT/3+10
		);

		cleanPanel();
		drawPanel();

		MLV_actualise_window();
		MLV_update_animation_player( animation_player );
		MLV_delay_according_to_frame_rate();
	}

	MLV_stop_animation_player( animation_player );
	MLV_rewind_animation_player( animation_player );

}

void rollUp(MLV_Animation_player* animation_player, int x, int y) {
	int i;

	MLV_play_revert_animation_player( animation_player );

	for (i = 0; i > -SLIME_SIZE; i = i-2) {
		MLV_draw_filled_rectangle(
			x*SLIME_SIZE + WINDOW_WIDTH/4+10,
			i + y*SLIME_SIZE + WINDOW_HEIGHT/3+10,
			SLIME_SIZE,
			SLIME_SIZE,
			MLV_COLOR_BLACK
		);

		MLV_draw_image_from_animation_player( 
			animation_player, 
			0, 
			x*SLIME_SIZE + WINDOW_WIDTH/4+10,
			i + y*SLIME_SIZE + WINDOW_HEIGHT/3+10
		);

		cleanPanel();
		drawPanel();

		MLV_actualise_window();
		MLV_update_animation_player( animation_player );
		MLV_delay_according_to_frame_rate();
	}

	MLV_stop_animation_player( animation_player );
	MLV_rewind_animation_player( animation_player );

}

void slimeJump(MLV_Animation_player* animation_player, int x, int y, int direction) {
	int i;

	MLV_play_animation_player( animation_player );

	for (i = 0; i < SLIME_SIZE; i = i+3) {
		MLV_draw_filled_rectangle(
			direction*i + x*SLIME_SIZE + WINDOW_WIDTH/4+10,
			y*SLIME_SIZE + WINDOW_HEIGHT/3+10,
			SLIME_SIZE,
			SLIME_SIZE,
			MLV_COLOR_BLACK
		);

		MLV_draw_image_from_animation_player( 
			animation_player, 
			0, 
			direction*i + x*SLIME_SIZE + WINDOW_WIDTH/4+10,
			y*SLIME_SIZE + WINDOW_HEIGHT/3+10
		);

		cleanPanel();
		drawPanel();


		MLV_actualise_window();
		/* Created too much frames */
		MLV_update_animation_player( animation_player );

		MLV_delay_according_to_frame_rate();
	}
	MLV_stop_animation_player( animation_player );
	MLV_rewind_animation_player( animation_player );
}