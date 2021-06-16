#include "recursive_backtrack.h"

static void recursive_backtrack(Tile tiles[ROWS][COLS], Tile *current) {
  Tile *neighbours[4];
  int neighbours_index = 0;

  Vector2 coords = coords_from_pos(current->position.x, current->position.y);

  // Add neighbouring tiles
  for (int i = -2; i < 3; i += 2) {
    for (int j = -2; j < 3; j += 2) {
      if (valid_tile(i, j, coords, 2)) {
        Tile *neighbour = &tiles[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type != WALL) {
          add_element(neighbour, neighbours, &neighbours_index);
        }
      }
    }
  }

  current->type = VISITED;

  // Select unvisited neighbours in a random order and recurse
  while (neighbours_index) {
    int neighbour_index = rand() % neighbours_index;
    Tile *neighbour = neighbours[neighbour_index];

    // If unvisited, remove separating wall and recurse on neighbour
    if (neighbour->type != VISITED) {
      tile_from_pos(tiles, (current->position.x + neighbour->position.x) / 2,
                    (current->position.y + neighbour->position.y) / 2)
          ->type = PASSAGE;
      recursive_backtrack(tiles, neighbour);
    }

    // Remove neighbour from neighbour set
    remove_element(neighbour_index, neighbours, &neighbours_index);
  }
}

void run_recursive_backtrack(Tile tiles[ROWS][COLS], Player player) {
  Tile *start = tile_from_pos(tiles, player.position.x, player.position.y);
  recursive_backtrack(tiles, start);
}
