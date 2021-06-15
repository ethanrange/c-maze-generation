#include "utils.h"

void remove_element(int index, Tile *array[], int *size) {
  // Shift elements down
  for (int i = index; i < *size - 1; i++) {
    array[i] = array[i + 1];
  }

  // Reduce size
  *size -= 1;
}

void add_element(Tile *element, Tile *array[], int *size) {
  array[*size] = element;
  *size += 1;
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

Tile *tile_from_pos(Tile tile[ROWS][COLS], int x, int y) {
  Vector2 coords = coords_from_pos(x, y);
  return &tile[(int)coords.y][(int)coords.x];
}

bool valid_pos(Tile tile[ROWS][COLS], int x, int y) {
  Tile *new_tile = tile_from_pos(tile, x, y);

  return (new_tile->type != WALL);
}