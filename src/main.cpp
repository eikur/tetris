/*tetris*/
#include "constants.h"
#include "video.h"
#include "Grid.h"
#include "Game.h"

int main (int argc, char *argv[] )
{
  //execution variables
  bool quit = false; 
  
  //event variables 
 SDL_Event event;

  //image variables // SDL2.0
  SDL_Window 	*myWindow = NULL;
  SDL_Renderer 	*myRenderer = NULL;

  //Code
  if ( init() == false)
  {
    std::cout << "Init error" << std::endl;
    std::cout << "SDL error : " << SDL_GetError() << std::endl;
    return 1;
  }
  
  myWindow = SDL_CreateWindow(SCREEN_CAPTION.c_str(), 
			      SDL_WINDOWPOS_CENTERED, 
			      SDL_WINDOWPOS_CENTERED, 
			      SCREEN_WIDTH, SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN);

  myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

  Game game( myWindow, myRenderer );

  while (!quit)
  {
    while( SDL_PollEvent( &event ) ){
      //If the user has Xed out the window
      if( event.type == SDL_QUIT )
      {
	  quit = true;
      }    
    }
    // Manage controls 
    // change from SDL 1.2 to SDL 2
    //Uint8 *keystates = SDL_GetKeyState( NULL ); // OLD
    const Uint8 *keystates = SDL_GetKeyboardState( NULL );
    if( keystates[SDL_SCANCODE_UP])
      game.input( KEY_UP );
    if (keystates[SDL_SCANCODE_DOWN])
      game.input( KEY_DOWN );
    if (keystates[SDL_SCANCODE_LEFT])
      game.input( KEY_LEFT);
    if (keystates[SDL_SCANCODE_RIGHT])
      game.input( KEY_RIGHT );
    if (keystates[SDL_SCANCODE_X])
      game.input( KEY_X );
    if (keystates[SDL_SCANCODE_Z])
      game.input( KEY_Z );
    if (keystates[SDL_SCANCODE_P])
      game.input( KEY_PAUSE );

    game.update_game();
    
    game.render_game();

    // this line is obsolete
    SDL_RenderPresent( myRenderer);
  }

  SDL_Quit();
  
  return 0;
}
