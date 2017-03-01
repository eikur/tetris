#pragma once
#include "constants.h"
#include "video.h"
#include "Grid.h"
#include "Timer.h"
#include "Level.h"

class Game
{
  /* // OLD SDL 1.2
private:
  SDL_Surface *screen_img;
  
  SDL_Surface *title_img;
  SDL_Surface *back_img;
  SDL_Surface *about_img;
  SDL_Surface *cursor_img;
  
  SDL_Surface *pause_msg;
  SDL_Surface *next_msg;
  SDL_Surface *tmp_msg;
  SDL_Color textColor;
  TTF_Font *font;
  
  int game_mode, menu_mode;
  int key_pressed;
  
  Grid *grid;
  Timer *timer;
  
  Level *level;
  
public: 
  Game( SDL_Surface*);	//Constructor
  void input( int );
  void spawn_piece( void );
  void update_game( void );
  void render_game( void );
  void calculate_positions( void );
  void render_HUD( void );
*/
private:
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  
  SDL_Texture *title_img = NULL;
  SDL_Texture *back_img = NULL;
  SDL_Texture *about_img = NULL;
  SDL_Texture *cursor_img = NULL;
  
  SDL_Texture *pause_msg;
  SDL_Texture *next_msg;
  SDL_Texture *tmp_msg;
  SDL_Color textColor;
  TTF_Font *font;
  
  int game_mode, menu_mode;
  int key_pressed;
  
  Grid *grid;
  Timer *timer;
  
  Level *level;
  
public: 
  Game( SDL_Window*, SDL_Renderer*);	//Constructor
  void input( int );
  void spawn_piece( void );
  void update_game( void );
  void render_game( void );
  void calculate_positions( void );
  void render_HUD( void );

};
