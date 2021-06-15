#include "recursive_backtrack.h"

static void recursive_backtrack(Tile tile[ROWS][COLS], Tile *current) {
  Tile *neighbours[4];
  int neighbours_index = 0;

  Vector2 coords = coords_from_pos(current->position.x, current->position.y);

  // Add neighbouring tiles
  for (int i = -2; i < 3; i += 2) {
    for (int j = -2; j < 3; j += 2) {
      if (abs(i) + abs(j) == 2 &&
          (coords.y + i >= 0 && (int)coords.y + i < ROWS) &&
          (coords.x + j >= 0 && (int)coords.x + j < COLS)) {

        Tile *neighbour = &tile[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type != WALL) {
          add_element(neighbour, neighbours, &neighbours_index);
        }
      }
    }
  }

  current->type = VISITED;

  while (neighbours_index) {
    int neighbour_index = rand() % neighbours_index;
    Tile *neighbour = neighbours[neighbour_index];

    if (neighbour->type != VISITED) {
      tile_from_pos(tile, (current->position.x + neighbour->position.x) / 2,
                    (current->position.y + neighbour->position.y) / 2)
          ->type = PASSAGE;
      recursive_backtrack(tile, neighbour);
    }

    remove_element(neighbour_index, neighbours, &neighbours_index);
  }
}

void run_recursive_backtrack(Tile tile[ROWS][COLS], Player player) {
  Tile *start = tile_from_pos(tile, player.position.x, player.position.y);
  recursive_backtrack(tile, start);
}