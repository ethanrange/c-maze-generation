#include "prims.h"

static Tile *walls[ROWS * COLS] = {0};
static int wall_index = 0;

void init_prims(Tile tile[ROWS][COLS], Player player) {
  // Logically clear walls array
  wall_index = 0;

  Vector2 coords = coords_from_pos(player.position.x, player.position.y);
  add_element(&tile[(int)coords.y][(int)coords.x], walls, &wall_index);
}

int step_prims(Tile tile[ROWS][COLS]) {
  int random_index = rand() % wall_index;
  Tile *random_wall = walls[random_index];

  Vector2 coords =
      coords_from_pos(random_wall->position.x, random_wall->position.y);

  // Find valid parent for all except start
  while (random_wall->type != START) {
    int i = (rand() % 3 - 1) * 2; // -2  0 or 2
    int j = (rand() % 3 - 1) * 2; // -2, 0 or 2

    if (abs(i) + abs(j) == 2 && (coords.y + i >= 0 && coords.y + i < ROWS) &&
        (coords.x + j >= 0 && coords.x + j < COLS)) {
      TileType parent_type = tile[(int)coords.y + i][(int)coords.x + j].type;

      if (parent_type == VISITED || parent_type == START) {
        tile[(int)coords.y + i / 2][(int)coords.x + j / 2].type = VISITED;
        break;
      }
    }
  }

  for (int i = -2; i < 3; i += 2) {
    for (int j = -2; j < 3; j += 2) {
      if (abs(i) + abs(j) == 2 &&
          (coords.y + i >= 0 && (int)coords.y + i < ROWS) &&
          (coords.x + j >= 0 && (int)coords.x + j < COLS)) {

        Tile *neighbour = &tile[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type == PASSAGE) {
          neighbour->type = FRONTIER;
          add_element(neighbour, walls, &wall_index);
        }
      }
    }
  }

  random_wall->type = VISITED;
  remove_element(random_index, walls, &wall_index);
  return wall_index;
}

void run_prims(Tile tile[ROWS][COLS], Player player) {
  while (wall_index) {
    step_prims(tile);
  }
}