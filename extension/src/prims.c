#include <assert.h>
#include <stdlib.h>

#include "raylib.h"
#include "constants.h"
#include "utils.h"
#include "prims.h"

static Tile *fringe[ROWS * COLS] = {0};
static int fringe_index = 0;

void init_prims(Tile tiles[ROWS][COLS], Player player) {
  // Logically clear fringe array
  fringe_index = 0;

  // Add starting tile to fringe
  Tile *start_tile = tile_from_pos(tiles, player.position.x, player.position.y);
  add_element(start_tile, fringe, &fringe_index);
}

int step_prims(Tile tiles[ROWS][COLS]) {
  // Select random fringe tile
  int random_index = rand() % fringe_index;
  Tile *random_tile = fringe[random_index];

  Vector2 coords =
      coords_from_pos(random_tile->position.x, random_tile->position.y);

  // Find random valid parent for all except start
  while (random_tile->type != START) {
    int i = rand_int(-1, 1) * 2; // -2, 0 or 2
    int j = rand_int(-1, 1) * 2; // -2, 0 or 2

    if (valid_tile(i, j, coords, 2)) {
      TileType parent_type = tiles[(int)coords.y + i][(int)coords.x + j].type;

      // If valid parent, remove separating wall
      if (parent_type == VISITED) {
        tiles[(int)coords.y + i / 2][(int)coords.x + j / 2].type = VISITED;
        break;
      }
    }
  }

  // Add neighbours to fringe
  for (int i = -2; i < 3; i += 2) {
    for (int j = -2; j < 3; j += 2) {
      if (valid_tile(i, j, coords, 2)) {
        Tile *neighbour = &tiles[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type == PASSAGE) {
          neighbour->type = FRINGE;
          add_element(neighbour, fringe, &fringe_index);
        }
      }
    }
  }

  random_tile->type = VISITED;
  remove_element(random_index, fringe, &fringe_index);
  return fringe_index;
}

void run_prims(Tile tiles[ROWS][COLS]) {
  assert(fringe_index >= 0);

  while (fringe_index > 0) {
    step_prims(tiles);
  }
}
