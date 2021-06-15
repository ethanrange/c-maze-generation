#ifndef UTILS
#define UTILS

#include "raylib.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef enum TileType {
  WALL,
  PASSAGE,
  START,
  VISITED,
  FRONTIER,
  GOAL,
  SEARCHED,
  PATH
} TileType;

typedef struct Tile Tile;

struct Tile {
  Tile *parent;
  Vector2 position;
  TileType type;
  int id;
  int weight;
};

typedef struct Player {
  Vector2 position;
} Player;

void remove_element(int index, Tile *array[], int *size);

void add_element(Tile *element, Tile *array[], int *size);

Vector2 coords_from_pos(int x, int y);

Tile *tile_from_pos(Tile tile[ROWS][COLS], int x, int y);

bool valid_pos(Tile tile[ROWS][COLS], int x, int y);

int get_min(Tile *array[], int *size);

#endif