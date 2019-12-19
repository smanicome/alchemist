#include <MLV/MLV_all.h>
#include "background.h"
#include "data.h"

int main() {
        MLV_create_window( "Alchemist", "alchemist", WINDOW_WIDTH, WINDOW_HEIGHT );
        drawBackground();
        MLV_actualise_window();
        MLV_wait_seconds( 60 );
        MLV_free_window();
        return 0;
}
