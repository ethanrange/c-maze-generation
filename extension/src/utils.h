// utils.h requires "raylib.h"
// utils.h requires "constants.h"

/** Represents the current state (halted or an algorithm) of the visualiser. */
typedef enum RunState {
  HALT,
  PRIMS,
  KRUSKALS,
  RECURSIVE_BACKTRACK,
  DIJKSTRAS
} RunState;

/** Stores the type of a tile. */
typedef enum TileType {
  WALL,
  PASSAGE,
  START,
  VISITED,
  FRINGE,
  GOAL,
  SEARCHED,
  PATH
} TileType;

/** Represents a tile in the visualiser's grid. */
typedef struct Tile {
  struct Tile *parent;
  Vector2 position;
  TileType type;
  int id;
  int weight;
} Tile;

/** Represents the starting point for some algorithms. */
typedef struct Player {
  Vector2 position;
} Player;

/**
 * Adds a tile to the given array of tiles.
 *
 * @param[in] element The pointer to the tile to be added.
 * @param[in,out] array The array of pointers to tiles.
 * @param[in,out] size The size of the array.
 */
void add_element(Tile *element, Tile *array[], int *size);

/**
 * Removes the tile at the given index from the given array of tiles.
 *
 * @param[in] index The index of the tile to be removed.
 * @param[in,out] array The array of pointers to tiles.
 * @param[in,out] size The size of the array.
 */
void remove_element(int index, Tile *array[], int *size);

/**
 * Finds the tile with the smallest weight in the given array.
 * 
 * @param[in] array The array of pointers to tiles.
 * @param[in] size The size of the array.
 * @return The index of the tile within the array.
 */
int get_min(Tile *array[], int *size);

/**
 * Find the (i, j) tile coordinate at the given (x, y) pixel coordinates.
 *
 * @param[in] x The x-coordinate.
 * @param[in] y The y-coordinate.
 * @return The tile coordinate at the specified pixel coordinates.
 */
Vector2 coords_from_pos(int x, int y);

/**
 * Finds the tile at the given (x, y) pixel coordinate.
 *
 * @param[in] tiles The visualiser's grid of tiles.
 * @param[in] x The x-coordinate of the requested tile.
 * @param[in] y The y-coordinate of the requested tile.
 * @return The tile at the specified coordinates.
 */
Tile *tile_from_pos(Tile tiles[ROWS][COLS], int x, int y);

/**
 * Checks if the desired player movement is valid.
 * 
 * @param[in] tiles The array of tiles.
 * @param[in] x The x-coordinate.
 * @param[in] y The y-coordinate.
 * @return True if the position is not a wall, false otherwise.
 */
bool valid_pos(Tile tiles[ROWS][COLS], int x, int y);

/**
 * Generates a random integer between min and max (inclusive).
 * 
 * @param[in] min The minimum value of the integer.
 * @param[in] max The maximum value of the integer.
 * @return The random integer.
 */
int rand_int(int min, int max);

/**
 * Checks if the given tile movement is valid in relation to the specified
 * coordinates.
 *
 * @param[in] i The tile x-coordinate.
 * @param[in] j The tile y-coordinate.
 * @param[in] coords The given current coordinates.
 * @param[in] dist The desired Manhattan distance between the coordinates.
 * @return True if the tile is within bounds and at the desired Manhattan
 * distance from the current coordinates, false otherwise.
 */
bool valid_tile(int i, int j, Vector2 coords, int dist);
