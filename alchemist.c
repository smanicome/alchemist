#include <MLV/MLV_all.h>

#include "game.h"
#include "data.h"

int main() {
	MLV_create_window( "Alchemist", "alchemist", WINDOW_WIDTH, WINDOW_HEIGHT );
	game();
	MLV_wait_seconds( 5 );
	MLV_free_window();
	return 0;
}
