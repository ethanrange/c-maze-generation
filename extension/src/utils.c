#include "utils.h"

/**
 * Removes the tile at the given index from the given array of tiles.
 *
 * @param[in] index The index of the tile to be removed.
 * @param[in,out] array The array of pointers to tiles.
 * @param[in,out] size The size of the array.
 */
void remove_element(int index, Tile *array[], int *size) {
  // Shift elements down
  for (int i = index; i < *size - 1; i++) {
    array[i] = array[i + 1];
  }

  // Decrement size
  (*size)--;
}

/**
 * Adds a tile to the given array of tiles.
 *
 * @param[in] element The pointer to the tile to be added.
 * @param[in,out] array The array of pointers to tiles.
 * @param[in,out] size The size of the array.
 */
void add_element(Tile *element, Tile *array[], int *size) {
  // Set next array element to element, and increment size
  array[(*size)++] = element;
}

// Find index of tile with smallest weight in given array
int get_min(Tile *array[], int *size) {
  int min_index = 0;
  int min_weight = __INT_MAX__;

  for (int i = 0; i < *size; i++) {
    if (array[i]->weight < min_weight) {
      min_index = i;
      min_weight = array[i]->weight;
    }
  }

  return min_index;
}

/**
 * Find the (i, j) tile coordinate at the given (x, y) pixel coordinates.
 *
 * @param[in] x The x-coordinate.
 * @param[in] y The y-coordinate.
 * @return The tile coordinate at the specified pixel coordinates.
 */
Vector2 coords_from_pos(int x, int y) {
  Vector2 coords = {0};

  if (x >= 0 && x <= screen_width && y >= 0 && y <= screen_height) {
    coords.x = x / (int)tile_size.x;
    coords.y = y / (int)tile_size.y;
    return coords;
  } else {
    perror("Invalid coordinate access\n");
    exit(EXIT_FAILURE);
  }
}

/**
 * Finds the tile at the given (x, y) pixel coordinate.
 *
 * @param[in] tiles The visualiser's grid of tiles.
 * @param[in] x The x-coordinate of the requested tile.
 * @param[in] y The y-coordinate of the requested tile.
 * @return The tile at the specified coordinates.
 */
Tile *tile_from_pos(Tile tiles[ROWS][COLS], int x, int y) {
  Vector2 coords = coords_from_pos(x, y);
  return &tiles[(int)coords.y][(int)coords.x];
}

// Check if desired player movement is valid
bool valid_pos(Tile tiles[ROWS][COLS], int x, int y) {
  Tile *new_tile = tile_from_pos(tiles, x, y);

  return (new_tile->type != WALL);
}

// Generate a random integer between min and max inclusive
int rand_int(int min, int max) { return (rand() % (max - min + 1)) + min; }

// check if in bounds
// and manhattan distance
bool valid_tile(int i, int j, Vector2 coords, int dist) {
  return (abs(i) + abs(j) == dist &&
          (coords.y + i >= 0 && coords.y + i < ROWS) &&
          (coords.x + j >= 0 && coords.x + j < COLS));
}
