// recursive_backtrack.h requires "raylib.h"
// recursive_backtrack.h requires "constants.h"
// recursive_backtrack.h requires "utils.h"

/**
 * Runs the recursive backtrack algorithm (i.e. a randomised depth-first search
 * algorithm).
 *
 * @param[in,out] tiles The visualiser's grid of tiles.
 * @return Returns bool to indicate success
 */
bool run_recursive_backtrack(Tile tiles[ROWS][COLS], Player player);
