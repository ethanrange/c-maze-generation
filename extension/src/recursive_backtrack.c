#include "recursive_backtrack.h"

static void recursive_backtrack(Tile tile[ROWS][COLS], Tile *current) {
  Tile *neighbours[4];
  int neighbours_index = 0;

  Vector2 coords = coords_from_pos(current->position.x, current->position.y);

  // Add neighbouring tiles
  for (int i = -2; i < 3; i += 2) {
    for (int j = -2; j < 3; j += 2) {
      if (valid_tile(i, j, coords, 2)) {
        Tile *neighbour = &tile[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type != WALL) {
          add_element(neighbour, neighbours, &neighbours_index);
        }
      }
    }
  }

  current->type = VISITED;

  // Select univisted neighbours in a random order and recurse
  while (neighbours_index) {
    int neighbour_index = rand() % neighbours_index;
    Tile *neighbour = neighbours[neighbour_index];

    // If unvisited, remove separating wall and recurse on neighbour
    if (neighbour->type != VISITED) {
      tile_from_pos(tile, (current->position.x + neighbour->position.x) / 2,
                    (current->position.y + neighbour->position.y) / 2)
          ->type = PASSAGE;
      recursive_backtrack(tile, neighbour);
    }

    // Remove neighbour from neighbour set
    remove_element(neighbour_index, neighbours, &neighbours_index);
  }
}

void run_recursive_backtrack(Tile tile[ROWS][COLS], Player player) {
  Tile *start = tile_from_pos(tile, player.position.x, player.position.y);
  recursive_backtrack(tile, start);
}