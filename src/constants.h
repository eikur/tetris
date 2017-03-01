#pragma once
/*
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include <iostream>
#include <string>
#include <vector>
#include <ctime>       
#include <sstream>

#define IDC2D(row,col) (((row)*(GRID_COL))+(col))
// L for Landed, F for Falling
#define XPOS_L(col) (col*TILE_PIXEL+GRID_XPOS)
#define YPOS_L(row) (row*TILE_PIXEL + GRID_YPOS)
#define XPOS_F(col,offset) ((col+offset)*TILE_PIXEL+GRID_XPOS)
#define YPOS_F(row,offset) ((row+offset)*TILE_PIXEL+GRID_YPOS)
#define XPOS_P(col)	(col*TILE_PIXEL + PREVIEW_XPOS)
#define YPOS_P(row)	(row*TILE_PIXEL + PREVIEW_YPOS)

//Screen parameters
const int SCREEN_WIDTH 	= 480;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP 	= 32;
const std::string SCREEN_CAPTION = "Tetris";

//tileset
const int TILE_PIXEL 	= 20; 

//Game modes 
const int GAME_TITLE	= 1;
const int GAME_PLAY	= 2;
const int GAME_PAUSE	= 3;
const int GAME_OVER	= 4;
const int GAME_ABOUT	= 5;

//key press code
const int KEY_NOKEY	= 0;	//No key is pressed
const int KEY_UP	= 1;	//Sudden drop
const int KEY_DOWN 	= 2;	//Swift drop
const int KEY_LEFT	= 3;	//Move to the left
const int KEY_RIGHT	= 4;	//Move to the right
const int KEY_X		= 5;	//rotate clockwise
const int KEY_Z 	= 6;	//rotate counter-clockwise
const int KEY_PAUSE	= 7;	// P button :P, for pausing

//Title menu codes
const int TITLE_NEW 	= 1;
const int TITLE_ABOUT	= 2;
const int TITLE_NEW_X	= 270;
const int TITLE_NEW_Y	= 485;
const int TITLE_ABOUT_X = TITLE_NEW_X;
const int TITLE_ABOUT_Y = TITLE_NEW_Y + 50;

//grid and layout parameters
const int GRID_COL 	= 10;
const int GRID_ROW 	= 16;

const int GRID_LEFT_COL	= 0;
const int GRID_RIGHT_COL = GRID_COL-1;
const int GRID_TOP_ROW 	= 0;
const int GRID_BOTTOM_ROW = GRID_ROW-1;

const int GRID_XPOS 	= 40; //2PX OFFSET IN LAYOUT
const int GRID_YPOS 	= 40;
const int GRID_LAY_BRDR = 2;
const int GRID_LAY_XPOS = GRID_XPOS - GRID_LAY_BRDR;
const int GRID_LAY_YPOS = GRID_YPOS - GRID_LAY_BRDR;


const int GRID_LEFT	= GRID_XPOS;
const int GRID_RIGHT	= GRID_XPOS + TILE_PIXEL*(GRID_COL-1);
const int GRID_TOP 	= GRID_YPOS;
const int GRID_BOTTOM	= GRID_YPOS + TILE_PIXEL+(GRID_ROW-1);

// piece spawn properties
const int SPAWN_XPOS 	= GRID_XPOS + 4*TILE_PIXEL;
const int SPAWN_YPOS	= GRID_YPOS;
const int SPAWN_COL	= 4;
const int SPAWN_ROW 	= 0;

// piece numbers 
const int TETRIS_O 	= 1;
const int TETRIS_Z 	= 2;
const int TETRIS_S 	= 3;
const int TETRIS_T 	= 4;
const int TETRIS_J 	= 5;
const int TETRIS_L 	= 6;
const int TETRIS_I	= 7;

//DELAYS
const int DELAY_DOWN	 = 60;
const int DELAY_SIDEWAYS = 120;
const int DELAY_ROTATION = 150;
const int DELAY_PAUSE	 = 200;
const int DELAY_GAMEOVER = 1000;


//PREVIEW PARAMETERS
const int PREVIEW_XPOS  = 300;
const int PREVIEW_YPOS  = 250;

//RESOURCES
const std::string RESOURCES_DIR = "../res/";
const std::string TITLE_IMAGE = RESOURCES_DIR + "title.png";
const std::string BACKGROUND_IMAGE = RESOURCES_DIR + "back.png"; 
//const std::string GRID_IMAGE = RESOURCES_DIR + "grid16x10.png";
const std::string GRID_IMAGE = RESOURCES_DIR + "grid16x10v2.png";
//const std::string BLOCKS_IMAGE = RESOURCES_DIR + "blocktiles.png"; 
const std::string BLOCKS_IMAGE = RESOURCES_DIR + "blocktiles2.png"; 
const std::string CURSOR_IMAGE = RESOURCES_DIR + "cursor.png";
const std::string ABOUT_IMAGE = RESOURCES_DIR + "about.png";
const std::string TEXT_FONT = RESOURCES_DIR + "aposiopesis_normal.ttf";

//TEXT COLOUR
const int TEXT_RED = 255;
const int TEXT_GREEN = 255;
const int TEXT_BLUE = 255;

// MESSAGE POSITIONS
const int MSG_LVL_XPOS = PREVIEW_XPOS;
const int MSG_LVL_YPOS = 120;
const int MSG_LINES_XPOS = PREVIEW_XPOS;
const int MSG_LINES_YPOS = MSG_LVL_YPOS + 30;
const int MSG_SCORE_XPOS = PREVIEW_XPOS;
const int MSG_SCORE_YPOS = MSG_LINES_YPOS + 30;
const int MSG_NEXT_XPOS = MSG_LVL_XPOS;
const int MSG_NEXT_YPOS = PREVIEW_YPOS - 30;
const int MSG_PAUSE_XPOS = MSG_LVL_XPOS;
const int MSG_PAUSE_YPOS = PREVIEW_YPOS + 90;


//LEVELS SPEED AND LIMITS
const int LVL1SPD	= 750;
const int LVL2SPD	= 650;
const int LVL3SPD	= 600;
const int LVL4SPD	= 550;
const int LVL5SPD	= 450;
const int LVL6SPD	= 350;
const int LVL7SPD	= 200;
const int LVL8SPD	= 150;
const int LVL9SPD	= 110;

const int LVL1LMT	= 10;
const int LVL2LMT	= LVL1LMT + 10;
const int LVL3LMT	= LVL2LMT + 10;
const int LVL4LMT	= LVL3LMT + 10;
const int LVL5LMT	= LVL4LMT + 10;
const int LVL6LMT	= LVL5LMT + 10;
const int LVL7LMT	= LVL6LMT + 10;
const int LVL8LMT	= LVL7LMT + 10;


