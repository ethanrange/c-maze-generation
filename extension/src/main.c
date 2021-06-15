#include "constants.h"
#include "dijkstras.h"
#include "kruskals.h"
#include "prims.h"
#include "raylib.h"
#include "recursive_backtrack.h"
#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Tile tile[ROWS][COLS] = {0};

static Player player = {0};

static RunState run = HALT;
static int remaining = 0;

static int (*step_funcs[5])() = {NULL, step_prims, step_kruskals, NULL,
                                 step_dijkstras};
static void (*init_funcs[5])() = {NULL, init_prims, init_kruskals, NULL,
                                  init_dijkstras};
static void (*run_funcs[5])() = {NULL, run_prims, run_kruskals, NULL,
                                 run_dijkstras};

static void init_game(void);
static void update_game(void);
static void draw_game(void);
static void update_draw_frame(void);

int main(void) {
  // Initialise random
  srand((unsigned int)time(NULL));

  // Initialise window
  InitWindow(screen_width, screen_height, "Maze Generation");

  // Initialise game
  init_game();

  // Target 60FPS
  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    update_draw_frame();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}

static void init_algorithm(RunState type) {
  // Initialise remaining to non-zero value
  remaining = 1;

  // Reset board for generation algorithms
  if (type != DIJKSTRA) {
    init_game();
  }

  if (init_funcs[type]) {
    (*init_funcs[type])(tile, player);
  }
}

static int step_algorithm(RunState type) {
  if (step_funcs[type]) {
    return (*step_funcs[type])(tile);
  }

  return 0;
}

static void run_algorithm(RunState type) {
  if (run_funcs[type]) {
    return (*run_funcs[type])(tile);
  }
}

static void handle_movement(int x_delta, int y_delta) {
  if (valid_pos(tile, player.position.x + x_delta,
                player.position.y + y_delta)) {
    player.position.x += x_delta;
    player.position.y += y_delta;
  }
}

static void handle_algorithm(RunState type) {
  // Initialise function
  init_algorithm(type);

  if (type == RECURSIVE_BACKTRACK) {
    run_recursive_backtrack(tile, player);
  } else {
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      run = run ? HALT : type;
    } else {
      run_algorithm(type);
    }
  }
};

void init_game(void) {

  // Initialize tiles
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      tile[i][j].position = (Vector2){j * tile_size.x + tile_size.x / 2,
                                      i * tile_size.y + tile_size.y / 2};

      tile[i][j].type = PASSAGE;

      // Set borders and grid pattern to walls
      if (!i || !j || (i == ROWS - 1) || (j == COLS - 1) || i % 2 == 0 ||
          j % 2 == 0) {
        tile[i][j].type = WALL;
      }

      // Unique ID for each tile
      tile[i][j].id = COLS * i + j;

      // Initialise weights to maximum
      tile[i][j].weight = __INT_MAX__;
    }
  }

  // Initialise start at bottom left tile
  Tile *start = &tile[ROWS - 2][1];

  player.position.x = start->position.x;
  player.position.y = start->position.y;

  start->type = START;
}

// Update game (one frame)
void update_game(void) {
  // Only start an algorithm if not currently running
  if (run == HALT) {
    if (IsKeyPressed('P')) {
      // Prims
      handle_algorithm(PRIM);
    } else if (IsKeyPressed('K')) {
      // Kruskals
      handle_algorithm(KRUSKAL);
    } else if (IsKeyPressed('B')) {
      // Recursive backtracking
      handle_algorithm(RECURSIVE_BACKTRACK);
    } else if (IsKeyPressed('D')) {
      // Dijkstras
      handle_algorithm(DIJKSTRA);
    }
  }

  if (run != HALT) {
    if (remaining) {
      remaining = step_algorithm(run);
    } else {
      run = HALT;
    }
  }

  // Reload maze
  if (IsKeyPressed('R')) {
    // Stop any current runs
    run = HALT;

    // Reinitialise game
    init_game();
    return;
  }

  // Handle player movement
  if (IsKeyPressed(KEY_UP)) {
    handle_movement(0, -tile_size.y);
  } else if (IsKeyPressed(KEY_DOWN)) {
    handle_movement(0, tile_size.y);
  } else if (IsKeyPressed(KEY_LEFT)) {
    handle_movement(-tile_size.x, 0);
  } else if (IsKeyPressed(KEY_RIGHT)) {
    handle_movement(tile_size.x, 0);
  }

  // Set goal on click
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    Vector2 position = GetMousePosition();
    Tile *selected = tile_from_pos(tile, position.x, position.y);

    selected->type = GOAL;
  }
}

void draw_game(void) {
  BeginDrawing();

  // Set blank background
  ClearBackground(RAYWHITE);

  // Draw tiles
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      DrawRectangle(tile[i][j].position.x - tile_size.x / 2,
                    tile[i][j].position.y - tile_size.y / 2, tile_size.x,
                    tile_size.y, colours[tile[i][j].type]);
    }
  }

  // Draw player
  DrawRectangle(player.position.x - player_size.x / 2,
                player.position.y - player_size.y / 2, player_size.x,
                player_size.y, RED);

  EndDrawing();
}

// Update and Draw (one frame)
void update_draw_frame(void) {
  update_game();
  draw_game();
}