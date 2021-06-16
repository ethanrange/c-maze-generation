typedef int (*StepFuncPtr)(Tile[ROWS][COLS]);
typedef void (*InitFuncPtr)(Tile[ROWS][COLS], Player);
typedef void (*RunFuncPtr)(Tile[ROWS][COLS]);

/** Initialises the tiles and start position of the visualiser. */
void init_visualiser(void);

/** Updates a single frame of the visualiser. */
void update_visualiser(void);

/** Draws the current state of the visualiser. */
void draw_visualiser(void);
