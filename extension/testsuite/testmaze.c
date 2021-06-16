#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "testutils.h"
#include "../raylib/src/raylib.h"
#include "../src/constants.h"
#include "../src/utils.h"


int main( void )
{
  Vector2 position_11 = {1, 1};
  Tile tile_11 = {NULL, position_11, START, 11, 10};

  Vector2 position_12 = {1, 2};
  Tile tile_12 = {NULL, position_12, WALL, 12, 20};

  Vector2 position_21 = {2, 1};
  Tile tile_21 = {NULL, position_21, PASSAGE, 21, 50};

  Vector2 position_22 = {2, 2};
  Tile tile_22 = {NULL, position_22, GOAL, 22, 80};

  Tile *tiles[4];
  int tiles_size = 0;

  //add_element tests
  add_element(&tile_11, tiles, &tiles_size);

  testint(tiles_size, 1, "tiles_size");
  testint(tiles[0]->id, 11, "tiles[0]->id");

  add_element(&tile_12, tiles, &tiles_size);
  
  testint(tiles_size, 2, "tiles_size");
  testint(tiles[1]->id, 12, "tiles[1]->id");

  add_element(&tile_21, tiles, &tiles_size);
  
  testint(tiles_size, 3, "tiles_size");
  testint(tiles[2]->id, 21, "tiles[2]->id");

  add_element(&tile_22, tiles, &tiles_size);
  
  testint(tiles_size, 4, "tiles_size");
  testint(tiles[3]->id, 22, "tiles[3]->id");

  //get_min tests

  testint(get_min(tiles, &tiles_size), 0, "smallest tile");

  //coords_from_pos tests

  Vector2 tmp = coords_from_pos(120, 200);
  testint((int)tmp.x, 3, "tmp.x");
  testint((int)tmp.y, 5, "tmp.y");

  //remove_element tests
  remove_element(2, tiles, &tiles_size);

  testint(tiles_size, 3, "tiles_size");
  testint(tiles[2]->id, 22, "tiles[2]->id");

  remove_element(2, tiles, &tiles_size);

  testint(tiles_size, 2, "tiles_size");
  testint(tiles[1]->id, 12, "tiles[1]->id");

  remove_element(1, tiles, &tiles_size);

  testint(tiles_size, 1, "tiles_size");
  testint(tiles[0]->id, 11, "tiles[0]->id");

  remove_element(0, tiles, &tiles_size);

  testint(tiles_size, 0, "tiles_size");
  testint(tiles[0]->id, 11, "tiles[0]->id");

  //tile_from_pos tests
  Tile tile_matrix[ROWS][COLS] = {{tile_11, tile_12}, {tile_21, tile_22}};

  testint(tile_from_pos(tile_matrix, 0, 0)->id, 11, "tile at (0, 0)->id");
  testint(tile_from_pos(tile_matrix, 40, 0)->id, 12, "tile at (1, 0)->id");
  testint(tile_from_pos(tile_matrix, 0, 40)->id, 21, "tile at (0, 1)->id");
  testint(tile_from_pos(tile_matrix, 40, 40)->id, 22, "tile at (1, 1)->id");

  //valid_pos tests
  testcond(valid_pos(tile_matrix, 0, 0), "Not WALL");
  testcond(!valid_pos(tile_matrix, 40, 0), "WALL");
  testcond(valid_pos(tile_matrix, 0, 40), "Not WALL");
  testcond(valid_pos(tile_matrix, 40, 40), "Not WALL");

  //valid_tile tests
  Vector2 middle = {25, 12};
  testcond(valid_tile(12, 25, middle, 37), "valid");
  testcond(!valid_tile(12, 25, middle, 38), "invalid dist");
  testcond(!valid_tile(13, 25, middle, 38), "x out of bound");
  testcond(!valid_tile(12, 26, middle, 38), "y out of bound");

	return(0);
}