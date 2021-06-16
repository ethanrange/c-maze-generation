#include <assert.h>

#include "constants.h"
#include "dijkstras.h"
#include "kruskals.h"
#include "prims.h"
#include "raylib.h"
#include "recursive_backtrack.h"
#include "utils.h"
#include "visualiser.h"

static const StepFuncPtr step_functions[5] = {NULL, step_prims, step_kruskals,
                                              NULL, step_dijkstras};
static const InitFuncPtr init_functions[5] = {NULL, init_prims, init_kruskals,
                                              NULL, init_dijkstras};
static const RunFuncPtr run_functions[5] = {NULL, run_prims, run_kruskals, NULL,
                                            run_dijkstras};

static const char *step_messages[5] = {
    NULL, "Visualising randomised Prim's maze-generation algorithm...",
    "Visualising randomised Kruskal's maze-generation algorithm...", NULL,
    "Visualising Dijkstra's pathfinding algorithm..."};

static const char *run_messages[5] = {
    NULL, "Ran randomised Prim's maze-generation algorithm",
    "Ran randomised Kruskal's maze-generation algorithm",
    "Ran recursive backtrack (randomised DFS) maze-generation algorithm",
    "Ran Dijkstra's pathfinding algorithm"};

static Tile tiles[ROWS][COLS] = {0};

static Player player = {0};

static RunState state = HALT;
static int remaining = 0;

static void init_algorithm(RunState type) {
  // Initialise remaining to non-zero value
  remaining = 1;

  // Reset board for generation algorithms
  if (type != DIJKSTRAS) {
    init_visualiser();
  }

  if (init_functions[type]) {
    (*init_functions[type])(tiles, player);
  }
}

static int step_algorithm(RunState type) {
  if (step_functions[type]) {
    SetWindowTitle(step_messages[type]);
    return (*step_functions[type])(tiles);
  }
  return 0;
}

static void run_algorithm(RunState type) {
  if (run_functions[type]) {
    SetWindowTitle(run_messages[type]);
    (*run_functions[type])(tiles);
  }
}

static void handle_movement(int x_delta, int y_delta) {
  if (valid_pos(tiles, player.position.x + x_delta,
                player.position.y + y_delta)) {
    player.position.x += x_delta;
    player.position.y += y_delta;
  }
}

static void handle_algorithm(RunState type) {
  // Initialise function
  init_algorithm(type);

  if (type == RECURSIVE_BACKTRACK) {
    SetWindowTitle(run_messages[type]);
    run_recursive_backtrack(tiles, player);
  } else {
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      state = state ? HALT : type;
    } else {
      run_algorithm(type);
    }
  }
}

static void halt_visualiser(void) {
  SetWindowTitle(DEFAULT_WINDOW_TITLE); // reset window title
  state = HALT;
}

void init_visualiser(void) {
  // Initialise tiles
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      tiles[i][j].position = (Vector2){j * tile_size.x + tile_size.x / 2,
                                       i * tile_size.y + tile_size.y / 2};

      tiles[i][j].type = PASSAGE;

      // Set borders and grid pattern to walls
      if (!i || !j || (i == ROWS - 1) || (j == COLS - 1) || i % 2 == 0 ||
          j % 2 == 0) {
        tiles[i][j].type = WALL;
      }

      // Unique ID for each tile
      tiles[i][j].id = COLS * i + j;

      // Initialise weights to maximum
      tiles[i][j].weight = __INT_MAX__;
    }
  }

  // Initialise start at bottom left tile
  Tile *start = &tiles[ROWS - 2][1];

  player.position.x = start->position.x;
  player.position.y = start->position.y;

  start->type = START;
}

void update_visualiser(void) {
  // Only start an algorithm if not currently running
  if (state == HALT) {
    if (IsKeyPressed('P')) {
      handle_algorithm(PRIMS);
    } else if (IsKeyPressed('K')) {
      handle_algorithm(KRUSKALS);
    } else if (IsKeyPressed('B')) {
      handle_algorithm(RECURSIVE_BACKTRACK);
    } else if (IsKeyPressed('D')) {
      handle_algorithm(DIJKSTRAS);
    }
  } else {
    if (remaining) {
      remaining = step_algorithm(state);
    } else {
      halt_visualiser();
    }
  }

  // Reload maze
  if (IsKeyPressed('R')) {
    // Stop any current runs
    halt_visualiser();

    // Re-initialise visualiser
    init_visualiser();
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
    Tile *selected = tile_from_pos(tiles, position.x, position.y);

    selected->type = GOAL;
  }
}

void draw_visualiser(void) {
  BeginDrawing();

  // Set blank background
  ClearBackground(RAYWHITE);

  // Draw tiles
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      DrawRectangle(tiles[i][j].position.x - tile_size.x / 2,
                    tiles[i][j].position.y - tile_size.y / 2, tile_size.x,
                    tile_size.y, colours[tiles[i][j].type]);
    }
  }

  // Draw player
  DrawRectangle(player.position.x - tile_size.x / 2,
                player.position.y - tile_size.y / 2, tile_size.x, tile_size.y,
                RED);

  EndDrawing();
}
