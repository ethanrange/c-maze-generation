#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "constants.h"
#include "utils.h"
#include "prims.h"
#include "kruskals.h"
#include "recursive_backtrack.h"
#include "dijkstras.h"
#include "visualiser.h"

int main(void) {
  // Initialise random
  srand((unsigned int)time(NULL));

  // Initialise window
  InitWindow(screen_width, screen_height, DEFAULT_WINDOW_TITLE);

  // Initialise visualiser
  init_visualiser();

  // Target 60FPS
  SetTargetFPS(60);

  // Main visualiser loop
  while (!WindowShouldClose()) {
    // Update and draw one frame
    update_visualiser();
    draw_visualiser();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
