#include <stdlib.h>

#include "raylib.h"
#include "constants.h"
#include "utils.h"
#include "dijkstras.h"

static Tile *fringe[ROWS * COLS] = {0};
static int fringe_index = 0;

void init_dijkstras(Tile tiles[ROWS][COLS], Player player) {
  // Logically clear fringe array
  fringe_index = 0;

  // Ensure only passages and goal and initialise parent to null
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (tiles[i][j].type != WALL && tiles[i][j].type != GOAL) {
        tiles[i][j].type = PASSAGE;
        tiles[i][j].parent = NULL;
      }
    }
  }

  // Add starting tile to fringe and zero weight
  Tile *start_tile = tile_from_pos(tiles, player.position.x, player.position.y);
  add_element(start_tile, fringe, &fringe_index);
  start_tile->weight = 0;
}

int step_dijkstras(Tile tiles[ROWS][COLS]) {
  // Select minimum weight fringe tile
  int index = get_min(fringe, &fringe_index);
  Tile *min_tile = fringe[index];

  Vector2 coords = coords_from_pos(min_tile->position.x, min_tile->position.y);

  // Add unvisited neighbours to fringe
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (valid_tile(i, j, coords, 1)) {
        Tile *neighbour = &tiles[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type == GOAL) {
          // On finding goal, backtrack and fill in path
          min_tile->type = PATH;

          while (min_tile->parent) {
            min_tile = min_tile->parent;
            min_tile->type = PATH;
          }

          // Return no remaining steps
          return 0;
        } else if (neighbour->type == PASSAGE) {
          neighbour->type = FRINGE;
          neighbour->weight = min_tile->weight + 1;
          neighbour->parent = min_tile;

          add_element(neighbour, fringe, &fringe_index);
        }
      }
    }
  }

  min_tile->type = SEARCHED;
  remove_element(index, fringe, &fringe_index);

  return fringe_index;
}

void run_dijkstras(Tile tiles[ROWS][COLS]) {
  int cont = 1;

  // While steps remaining and fringe tiles left to search
  while (cont > 0) {
    cont = step_dijkstras(tiles);
  }
}
