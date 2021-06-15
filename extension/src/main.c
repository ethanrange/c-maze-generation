#include "constants.h"
#include "kruskals.h"
#include "prims.h"
#include "raylib.h"
#include "recursive_backtrack.h"
#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static bool game_over = false;
static bool pause = false;

static Tile tile[ROWS][COLS] = {0};

static Player player = {0};

static int run = 0;
static int remaining = 0;

static void init_game(void);
static void update_game(void);
static void draw_game(void);
static void unload_game(void);
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

  unload_game();

  CloseWindow();

  return EXIT_SUCCESS;
}

static int step_algorithm(int type) {
  switch (type) {
  case 1:
    return step_prims(tile);
  case 2:
    return step_kruskals(tile);
  default:
    return 0;
  }
}

static void init_algorithm(int type) {
  init_game();
  remaining = 1; // Initialise to non-zero

  switch (type) {
  case 0:
    init_prims(tile, player);
    break;
  case 1:
    init_kruskals(tile);
    break;
  }
}

void init_game(void) {

  // Initialize tiles

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      tile[i][j].position = (Vector2){j * tile_size.x + tile_size.x / 2,
                                      i * tile_size.y + tile_size.y / 2};

      tile[i][j].type = PASSAGE;

      if (!i || !j || (i == ROWS - 1) || (j == COLS - 1) || i % 2 == 0 ||
          j % 2 == 0) {
        tile[i][j].type = WALL;
      }

      tile[i][j].id = COLS * i + j;
    }
  }

  while (true) {
    int i = ROWS - 2; //((double)rand() / (double)RAND_MAX) * (ROWS - 2) + 1;
    int j = 1;        //((double)rand() / (double)RAND_MAX) * (COLS - 2) + 1;

    if (tile[i][j].type == PASSAGE) {
      player.position.x = tile[i][j].position.x;
      player.position.y = tile[i][j].position.y;

      tile[i][j].type = START;

      break;
    }
  }
}

// Update game (one frame)
void update_game(void) {
  if (!game_over) {
    if (IsKeyPressed('P')) {
      // Toggle pause
      pause = !pause;
    }

    // Step generation function
    if (IsKeyPressed('W')) {
      init_algorithm(0);

      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        run = run ? 0 : 1;
      } else {
        run_prims(tile, player);
      }
    } else if (IsKeyPressed('K')) {
      init_algorithm(1);

      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        run = run ? 0 : 2;
      } else {
        run_kruskals(tile);
      }
    } else if (IsKeyPressed('B')) {
      init_algorithm(2);
      run_recursive_backtrack(tile, player);
    }

    if (run && remaining) {
      remaining = step_algorithm(run);
    } else {
      run = 0;
    }

    if (IsKeyPressed('R')) {
      // Reload maze
      init_game();
      return;
    }

    // Vector2 position = GetMousePosition();

    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    //   Vector2 coords = coords_from_pos(position.x, position.y);
    //   Tile *selected = tile_from_pos(tile, position.x, position.y);
    //   printf("Id: %i Type: %i Coords: %i %i\n", get_id(selected->id),
    //          selected->type, (int)coords.x, (int)coords.y);
    // }

    // Refactor to a switch?
    if (IsKeyPressed(KEY_UP)) {
      if (valid_pos(tile, player.position.x, player.position.y - tile_size.y)) {
        player.position.y -= tile_size.y;
      }
    } else if (IsKeyPressed(KEY_DOWN)) {
      if (valid_pos(tile, player.position.x, player.position.y + tile_size.y)) {
        player.position.y += tile_size.y;
      }
    } else if (IsKeyPressed(KEY_LEFT)) {
      if (valid_pos(tile, player.position.x - tile_size.x, player.position.y)) {
        player.position.x -= tile_size.x;
      }
    } else if (IsKeyPressed(KEY_RIGHT)) {
      if (valid_pos(tile, player.position.x + tile_size.x, player.position.y)) {
        player.position.x += tile_size.x;
      }
    }
  }
}

void draw_game(void) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  // Draw tiles
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      DrawRectangle(tile[i][j].position.x - tile_size.x / 2,
                    tile[i][j].position.y - tile_size.y / 2, tile_size.x,
                    tile_size.y, colours[tile[i][j].type]);
    }
  }

  if (!pause) {
    DrawRectangle(player.position.x - 20, player.position.y - 20, 40, 40, RED);
  } else {
    DrawText(FormatText("Pos %i %i", GetMouseX(), GetMouseY()),
             screen_width / 2 - MeasureText("GAME PAUSED", 40) / 2,
             screen_height / 2 - 40, 40, WHITE);
  }

  EndDrawing();
}

// Unload game variables
void unload_game(void) {
  // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void update_draw_frame(void) {
  update_game();
  draw_game();
}