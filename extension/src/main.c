#include "raylib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 25
#define COLS 51

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Brick {
  Vector2 position;
  int col;
} Brick;

typedef struct Player {
  Vector2 position;
} Player;

static const int screenWidth = 2040;
static const int screenHeight = 1000;

static bool game_over = false;
static bool pause = false;

static Brick brick[ROWS][COLS] = {0};
static Vector2 brick_size = {0};

static const Color colours[3] = {GRAY, DARKGRAY, GREEN};

static Player player = {0};
static Vector2 player_size = {0};

static void init_game(void);
static void update_game(void);
static void draw_game(void);
static void unload_game(void);
static void update_draw_frame(void);

int main(void) {
  // Initialise random
  srand((unsigned int)time(NULL));

  InitWindow(screenWidth, screenHeight, "Maze Generation");

  init_game();

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    update_draw_frame();
  }

  unload_game();

  CloseWindow();

  return EXIT_SUCCESS;
}

void init_game(void) {
  brick_size = (Vector2){40, 40};
  player_size = (Vector2){40, 40};

  // Initialize bricks

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      brick[i][j].position = (Vector2){j * brick_size.x + brick_size.x / 2,
                                       i * brick_size.y + brick_size.y / 2};

      if (!i || !j || (i == ROWS - 1) || (j == COLS - 1)) {
        // Draw border with randomised green
        brick[i][j].col = ((double)rand() / (double)RAND_MAX) < 0.01 ? 2 : 1;
      } else if (i % 2 == 0 || j % 2 == 0) {
        // Randomise grid pattern
        brick[i][j].col = ((double)rand() / (double)RAND_MAX) < 0.5 ? 0 : 1;
      } else {
        brick[i][j].col = 0;
      }
    }
  }

  // Set player is first free tile from lower left

  for (int i = 1; i < ROWS - 1; i++) {
    for (int j = COLS - 1; j > 0; j--) {
      if (!brick[i][j].col) {
        player.position.x = brick[i][j].position.x;
        player.position.y = brick[i][j].position.y;
      }
    }
  }
}

bool valid_pos(int x, int y) {
  if (brick[y / 40][x / 40].col == 2) {
    // Reload on touching green
    init_game();
    return false;
  } else {
    // Check in bounds and valid tile
    return (x >= 60 && x <= 1980 && y >= 60 && y <= 940 &&
            !(brick[y / 40][x / 40].col));
  }
}

// Update game (one frame)
void update_game(void) {
  if (!game_over) {
    if (IsKeyPressed('P')) {
      // Toggle pause
      pause = !pause;
    }

    if (IsKeyPressed('R')) {
      // Reload maze
      init_game();
      return;
    }

    Vector2 position = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      brick[(int)position.y / (int)brick_size.y]
           [(int)position.x / (int)brick_size.x]
               .col = 2;
    }

    if (IsKeyPressed(KEY_UP)) {
      if (valid_pos(player.position.x, player.position.y - brick_size.y)) {
        player.position.y -= brick_size.y;
      }
    } else if (IsKeyPressed(KEY_DOWN)) {
      if (valid_pos(player.position.x, player.position.y + brick_size.y)) {
        player.position.y += brick_size.y;
      }
    } else if (IsKeyPressed(KEY_LEFT)) {
      if (valid_pos(player.position.x - brick_size.x, player.position.y)) {
        player.position.x -= brick_size.x;
      }
    } else if (IsKeyPressed(KEY_RIGHT)) {
      if (valid_pos(player.position.x + brick_size.x, player.position.y)) {
        player.position.x += brick_size.x;
      }
    }
  }
}

void draw_game(void) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  if (!game_over) {
    // Draw bricks
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        DrawRectangle(brick[i][j].position.x - brick_size.x / 2,
                      brick[i][j].position.y - brick_size.y / 2, brick_size.x,
                      brick_size.y, colours[brick[i][j].col]);
      }
    }

    if (!pause) {
      DrawRectangle(player.position.x - 20, player.position.y - 20, 40, 40,
                    RED);
    } else {
      DrawText(FormatText("Pos %i %i", GetMouseX(), GetMouseY()),
               screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2,
               screenHeight / 2 - 40, 40, WHITE);
    }
  } else {
    DrawText("PRESS [ENTER] TO PLAY AGAIN",
             GetScreenWidth() / 2 -
                 MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
             GetScreenHeight() / 2 - 50, 20, GRAY);
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