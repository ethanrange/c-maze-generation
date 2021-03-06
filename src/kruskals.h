// kruskals.h requires "raylib.h"
// kruskals.h requires "constants.h"
// kruskals.h requires "utils.h"

/**
 * Initialises the required variables for Kruskal's algorithm.
 *
 * @param[in] tiles The visualiser's grid of tiles.
 * @param player The player. This argument is unused but necessary to match the
 * type signature of every algorithm initialisation function.
 */
void init_kruskals(Tile tiles[ROWS][COLS], Player player);

/**
 * Performs a single iteration of Kruskal's algorithm.
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 * @return The number of wall tiles remaining. Zero signifies the algorithm is
 * complete.
 */
int step_kruskals(Tile tiles[ROWS][COLS]);

/**
 * Runs the randomised Kruskal's algorithm.
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 * @return Returns bool to indicate success
 */
bool run_kruskals(Tile tiles[ROWS][COLS]);
