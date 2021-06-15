#include "kruskals.h"

static Tile *walls[ROWS * COLS] = {0};
static int wall_index = 0;

int parent[ROWS * COLS] = {0};

static int get_id(int id) {
  while (parent[id]) {
    id = parent[id];
  }

  return id;
}

void init_kruskals(Tile tile[ROWS][COLS]) {
  // Logically clear walls array
  wall_index = 0;

  // Reset parent array
  memset(parent, 0, sizeof(parent));

  // Add horizontal walls to walls list
  for (int i = 1; i < ROWS - 1; i += 2) {
    for (int j = 2; j < COLS - 2; j += 2) {
      add_element(&tile[i][j], walls, &wall_index);
    }
  }

  // Add vertical walls to walls list
  for (int i = 2; i < ROWS - 2; i += 2) {
    for (int j = 1; j < COLS - 1; j += 2) {
      add_element(&tile[i][j], walls, &wall_index);
    }
  }

  printf("Initialised Kruskals\n");
}

int step_kruskals(Tile tile[ROWS][COLS]) {
  int random_index = rand() % wall_index;
  Tile *random_wall = walls[random_index];

  Vector2 coords =
      coords_from_pos(random_wall->position.x, random_wall->position.y);

  Tile *neighbours[2];
  int neighbours_index = 0;

  // Add neighbouring tiles
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (abs(i) + abs(j) == 1 &&
          (coords.y + i >= 0 && (int)coords.y + i < ROWS) &&
          (coords.x + j >= 0 && (int)coords.x + j < COLS)) {

        Tile *neighbour = &tile[(int)coords.y + i][(int)coords.x + j];

        if (neighbour->type != WALL) {
          neighbours[neighbours_index] = neighbour;
          neighbours_index++;
        }
      }
    }
  }

  // Union ids
  int neighbour0_id = get_id(neighbours[0]->id);
  int neighbour1_id = get_id(neighbours[1]->id);
  int wall_id = get_id(random_wall->id);

  if (neighbour0_id != neighbour1_id) {
    random_wall->type = PASSAGE;

    if (neighbour0_id < neighbour1_id) {
      parent[neighbour1_id] = neighbour0_id;
      parent[wall_id] = neighbour0_id;
    } else {
      parent[neighbour0_id] = neighbour1_id;
      parent[wall_id] = neighbour1_id;
    }
  }

  remove_element(random_index, walls, &wall_index);
  return wall_index;
}

void run_kruskals(Tile tile[ROWS][COLS]) {
  printf("Running Kruskals\n");
  
  while (wall_index) {
    step_kruskals(tile);
  }
}