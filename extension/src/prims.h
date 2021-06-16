// prims.h requires "raylib.h"
// prims.h requires "constants.h"
// prims.h requires "utils.h"

/**
 * Initialises the required variables for Prim's algorithm.
 *
 * @param[in] tiles The visualiser's grid of tiles.
 * @param[in] player The player.
 */
void init_prims(Tile tiles[ROWS][COLS], Player player);

/**
 * Performs a single iteration of Prim's algorithm.
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 * @return The number of fringe tiles remaining. Zero signifies the algorithm is
 * complete.
 */
int step_prims(Tile tiles[ROWS][COLS]);

/**
 * Runs the randomised Prim's algorithm.
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 * @return Returns bool to indicate success
 */
bool run_prims(Tile tiles[ROWS][COLS]);
