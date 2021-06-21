// constants.h requires "raylib.h"

#define DEFAULT_WINDOW_TITLE "Maze Generation Visualiser"

/* Screen width and height depend on the tile width */
#define TILE_WIDTH 40

#define ROWS 25
#define COLS 51

static const Vector2 tile_size = {TILE_WIDTH, TILE_WIDTH};

static const int screen_width = TILE_WIDTH * COLS;
static const int screen_height = TILE_WIDTH * ROWS;

static const Color colours[8] = {DARKGRAY, GRAY,  RED,    GRAY,
                                 BLUE,     GREEN, ORANGE, PURPLE};
