#pragma once
#include "constants.h"
#include "video.h"
#include "Piece.h"

class Grid
{
private:
   int* grid;
   //SDL_Surface *layout; 
   SDL_Texture *layout;
   //SDL_Surface *blocks;
   SDL_Texture *blocks;
   SDL_Rect *bclip;
   
   int lines;
   
   
   int next;
   Piece *piece;
   Piece *preview;

   bool gameover;

   //addition
  SDL_Renderer *renderer = NULL;
   
public:
  //Grid();
  Grid(SDL_Renderer*);
  ~Grid();
  void reset_grid( void );
  
  void spawn_piece( void );
  void next_piece( void );
  
  void update( int );
  void move_left( void );
  void move_right( void );
  void move_down( void );
  void rotate( void );
  
  void copy2grid( void );
  void check_lines( void );
  void clear_line( int* );
  int  lines2add( void );
  
  //void render( SDL_Surface*);
  void render( SDL_Renderer* );
  
  bool is_gameover( void );
  
};
