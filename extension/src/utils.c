#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "constants.h"
#include "utils.h"

void add_element(Tile *element, Tile *array[], int *size) {
  // Set next array element to element, and increment size
  array[(*size)++] = element;
}

void remove_element(int index, Tile *array[], int *size) {
  // Shift elements down
  for (int i = index; i < *size - 1; i++) {
    array[i] = array[i + 1];
  }

  // Decrement size
  (*size)--;
}

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

Tile *tile_from_pos(Tile tiles[ROWS][COLS], int x, int y) {
  Vector2 coords = coords_from_pos(x, y);
  return &tiles[(int)coords.y][(int)coords.x];
}

bool valid_pos(Tile tiles[ROWS][COLS], int x, int y) {
  Tile *new_tile = tile_from_pos(tiles, x, y);
  return (new_tile->type != WALL);
}

int rand_int(int min, int max) { return (rand() % (max - min + 1)) + min; }

bool valid_tile(int i, int j, Vector2 coords, int dist) {
  return (abs(i) + abs(j) == dist &&
          (coords.y + i >= 0 && coords.y + i < ROWS) &&
          (coords.x + j >= 0 && coords.x + j < COLS));
}
