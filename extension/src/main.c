#include "raylib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 25
#define COLS 51

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef enum TileType {
  WALL,
  PASSAGE,
  START,
  VISITED,
  FRONTIER,
  GOAL
} TileType;

typedef struct Tile {
  Vector2 position;
  TileType type;
} Tile;

typedef struct Player {
  Vector2 position;
} Player;

static const int screen_width = 2040;
static const int screen_height = 1000;

static bool game_over = false;
static bool pause = false;

static Tile tile[ROWS][COLS] = {0};
static Vector2 tile_size = {0};

static const Color colours[6] = {DARKGRAY, GRAY, RED, GRAY, BLUE, GREEN};

static Player player = {0};
static Vector2 player_size = {0};

Tile *walls[ROWS * COLS] = {0};
int wall_index = 0;

int remaining_tiles = 0;

static void init_game(void);
static void update_game(void);
static void draw_game(void);
static void unload_game(void);
static void update_draw_frame(void);

static void remove_element(int index) {
  // Shift elements down
  for (int i = index; i < wall_index - 1; i++) {
    walls[i] = walls[i + 1];
  }

  // Reduce size
  wall_index--;
}

static void add_element(Tile *element) {
  walls[wall_index] = element;
  wall_index++;
}

int main(void) {
  // Initialise random
  srand((unsigned int)time(NULL));

  InitWindow(screen_width, screen_height, "Maze Generation");

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

Vector2 coords_from_pos(int x, int y) {
  Vector2 coords = {0};

  if (x >= 0 && x <= screen_width && y >= 0 && y <= screen_height) {
    coords.x = x / (int)tile_size.x;
    coords.y = y / (int)tile_size.y;

    return coords;
  } else {
    perror("Invalid coordinate access\n");
    exit(EXIT_FAILURE);
  }
}

Tile *tile_from_pos(int x, int y) {
  Vector2 coords = coords_from_pos(x, y);
  return &tile[(int)coords.y][(int)coords.x];
}

bool valid_pos(int x, int y) {
  Tile *tile = tile_from_pos(x, y);

  if (tile->type == GOAL) {
    init_game();
    return false;
  }

  return (tile->type != WALL);
}

void step_prims(void) {
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
          add_element(neighbour);
        }
      }
    }
  }

  random_wall->type = VISITED;
  remove_element(random_index);
}

void run_prims(void) {
  // init_game();

  while (remaining_tiles) {
    step_prims();
    remaining_tiles--;
  }
}

void init_game(void) {
  tile_size = (Vector2){40, 40};
  player_size = (Vector2){40, 40};

  remaining_tiles = ((ROWS - 1) / 2) * ((COLS - 1) / 2);

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
    }
  }

  wall_index = 0;

  while (true) {
    int i = ROWS - 2; //((double)rand() / (double)RAND_MAX) * (ROWS - 2) + 1;
    int j = 1;        //((double)rand() / (double)RAND_MAX) * (COLS - 2) + 1;

    if (tile[i][j].type == PASSAGE) {
      player.position.x = tile[i][j].position.x;
      player.position.y = tile[i][j].position.y;

      tile[i][j].type = START;

      add_element(&tile[i][j]);

      break;
    }
  }

  run_prims();

  // Set goal
  tile[1][COLS - 2].type = GOAL;
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
      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        step_prims();
      } else {
        run_prims();
      }
    }

    if (IsKeyPressed('R')) {
      // Reload maze
      init_game();
      return;
    }

    // Vector2 position = GetMousePosition();

    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    //   tile_from_pos(position.x, position.y)->col = 2;
    // }

    // Refactor to a switch?
    if (IsKeyPressed(KEY_UP)) {
      if (valid_pos(player.position.x, player.position.y - tile_size.y)) {
        player.position.y -= tile_size.y;
      }
    } else if (IsKeyPressed(KEY_DOWN)) {
      if (valid_pos(player.position.x, player.position.y + tile_size.y)) {
        player.position.y += tile_size.y;
      }
    } else if (IsKeyPressed(KEY_LEFT)) {
      if (valid_pos(player.position.x - tile_size.x, player.position.y)) {
        player.position.x -= tile_size.x;
      }
    } else if (IsKeyPressed(KEY_RIGHT)) {
      if (valid_pos(player.position.x + tile_size.x, player.position.y)) {
        player.position.x += tile_size.x;
      }
    }
  }
}

void draw_game(void) {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  if (!game_over) {
    // Draw tiles
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        DrawRectangle(tile[i][j].position.x - tile_size.x / 2,
                      tile[i][j].position.y - tile_size.y / 2, tile_size.x,
                      tile_size.y, colours[tile[i][j].type]);
      }
    }

    if (!pause) {
      DrawRectangle(player.position.x - 20, player.position.y - 20, 40, 40,
                    RED);
    } else {
      DrawText(FormatText("Pos %i %i", GetMouseX(), GetMouseY()),
               screen_width / 2 - MeasureText("GAME PAUSED", 40) / 2,
               screen_height / 2 - 40, 40, WHITE);
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