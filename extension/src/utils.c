#include "utils.h"

void remove_element(int index, Tile *array[], int *size) {
  // Shift elements down
  for (int i = index; i < *size - 1; i++) {
    array[i] = array[i + 1];
  }

  // Decrement size
  *size -= 1;
}

void add_element(Tile *element, Tile *array[], int *size) {
  // Set next array element to element
  array[*size] = element;

  // Increment size
  *size += 1;
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

// Find i j coordinates from x y position
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

// Find tile at x y position
Tile *tile_from_pos(Tile tile[ROWS][COLS], int x, int y) {
  Vector2 coords = coords_from_pos(x, y);
  return &tile[(int)coords.y][(int)coords.x];
}

// Check if desired player movement is valid
bool valid_pos(Tile tile[ROWS][COLS], int x, int y) {
  Tile *new_tile = tile_from_pos(tile, x, y);

  return (new_tile->type != WALL);
}

// Generate a random integer between min and max inclusive
int rand_int(int min, int max) { return (rand() % (max - min + 1)) + min; }

bool valid_tile(int i, int j, Vector2 coords, int dist) {
  return (abs(i) + abs(j) == dist && (coords.y + i >= 0 && coords.y + i < ROWS) &&
          (coords.x + j >= 0 && coords.x + j < COLS));
}