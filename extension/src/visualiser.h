// visualiser.h requires "raylib.h"
// visualiser.h requires "constants.h"
// visualiser.h requires "utils.h"
// visualiser.h requires "prims.h"
// visualiser.h requires "kruskals.h"
// visualiser.h requires "recursive_backtrack.h"
// visualiser.h requires "dijkstras.h"

typedef int (*StepFuncPtr)(Tile[ROWS][COLS]);
typedef void (*InitFuncPtr)(Tile[ROWS][COLS], Player);
typedef void (*RunFuncPtr)(Tile[ROWS][COLS]);

/** Initialises the tiles and start position of the visualiser. */
void init_visualiser(void);

/** Updates a single frame of the visualiser. */
void update_visualiser(void);

/** Draws the current state of the visualiser. */
void draw_visualiser(void);
