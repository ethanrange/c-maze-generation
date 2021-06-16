#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "raylib.h"

typedef enum RunState {
  HALT,
  PRIMS,
  KRUSKALS,
  RECURSIVE_BACKTRACK,
  DIJKSTRAS
} RunState;

typedef enum TileType {
  WALL,
  PASSAGE,
  START,
  VISITED,
  FRINGE,
  GOAL,
  SEARCHED,
  PATH
} TileType;

typedef struct Tile {
  struct Tile *parent;
  Vector2 position;
  TileType type;
  int id;
  int weight;
} Tile;

typedef struct Player {
  Vector2 position;
} Player;

void remove_element(int index, Tile *array[], int *size);

void add_element(Tile *element, Tile *array[], int *size);

int get_min(Tile *array[], int *size);

Vector2 coords_from_pos(int x, int y);

Tile *tile_from_pos(Tile tiles[ROWS][COLS], int x, int y);

bool valid_pos(Tile tiles[ROWS][COLS], int x, int y);

int rand_int(int min, int max);

bool valid_tile(int i, int j, Vector2 coords, int dist);

#endif
