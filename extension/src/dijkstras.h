#include "constants.h"
#include "utils.h"

/**
 * Initialises the required variables for Dijkstra's algorithm.
 *
 * @param[in] tiles The visualiser's grid of tiles.
 * @param player The player.
 */
void init_dijkstras(Tile tiles[ROWS][COLS], Player player);

/**
 * Performs a single iteration of Dijkstra's algorithm.
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 * @return The number of fringe tiles remaining to search. Zero signifies the
 * search is complete.
 */
int step_dijkstras(Tile tiles[ROWS][COLS]);

/**
 * Runs Dijkstra's algorithm for maze-solving.
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 */
void run_dijkstras(Tile tiles[ROWS][COLS]);
