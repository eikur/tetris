#include "Game.h"

Game::Game(SDL_Window *wndw, SDL_Renderer *rndrr)
{
  //image variables
  window = wndw;
  renderer = rndrr;
  
  title_img = load_image(TITLE_IMAGE,renderer);
  back_img = load_image(BACKGROUND_IMAGE,renderer);
  about_img = load_image(ABOUT_IMAGE,renderer);
  cursor_img = load_image(CURSOR_IMAGE,renderer);
  
  if (title_img == NULL || back_img == NULL || about_img == NULL || cursor_img == NULL )
    std::cout << "Resources error: load from Game class" << std::endl;
  
  //game objects
  grid = new Grid( renderer );
  timer = new Timer();
  level = new Level();

  //flow variables
  game_mode 	= GAME_TITLE;
  menu_mode 	= TITLE_NEW;
  
  //text variables
  font = TTF_OpenFont( TEXT_FONT.c_str(), 28);
  textColor.r = TEXT_RED;   textColor.g = TEXT_GREEN;  textColor.b = TEXT_BLUE; 

  // messages
  /*
  pause_msg = TTF_RenderText_Solid( font, "Pause", textColor);
  next_msg = TTF_RenderText_Solid( font, "Next", textColor );
  */
  pause_msg = render_text(font, "Pause", textColor, renderer);
  next_msg = render_text(font, "Next", textColor, renderer);
}

void Game::input( int key )
{
    switch (game_mode)
    {
      case GAME_TITLE:
	if (menu_mode == TITLE_NEW)
	{
	  timer->delay(DELAY_PAUSE);
	  if (key == KEY_DOWN)		
	    menu_mode = TITLE_ABOUT;	    
	  else if (key == KEY_PAUSE )   
	    game_mode = GAME_PLAY;
	}
	else if (menu_mode == TITLE_ABOUT)
	{
	  timer->delay(DELAY_PAUSE);
	  if (key == KEY_UP )		 menu_mode = TITLE_NEW;
	  else if (key == KEY_PAUSE )	 game_mode = GAME_ABOUT;
	}
      break;	
    
      case GAME_PLAY:
	if (key == KEY_PAUSE){
	  timer->delay(DELAY_PAUSE);
	  timer->chrono(true, level->get_speed() );
	  game_mode = GAME_PAUSE;
	}
        else if (key == KEY_LEFT || key == KEY_RIGHT ){
	  timer->delay(DELAY_SIDEWAYS);
	  grid->update(key);
	}
	else if (key == KEY_UP){
	  timer->delay(DELAY_ROTATION);
	  grid->update( key );
	}
	else if (key == KEY_DOWN){
	    timer->delay( DELAY_DOWN);
	    timer->chrono(false, level->get_speed() );
	    grid->update(key);
	}
      break;      
    
      case GAME_PAUSE:
      if (key == KEY_PAUSE) 
      {
	timer->delay(DELAY_PAUSE);
	timer->chrono(true, level->get_speed());
	game_mode = GAME_PLAY;
      }
      break;

      case GAME_OVER: 	game_mode = GAME_TITLE; break;
    
      case GAME_ABOUT: 	game_mode = GAME_TITLE; break;
  }
}


void Game::update_game( void ) //no need for updating if we're not playing
{
  if (game_mode == GAME_PLAY)
  {
    if (timer->chrono( false, level->get_speed() ))
    {
     grid->update( KEY_DOWN ); 
    }
    if (grid->is_gameover())
      game_mode = GAME_OVER;
    level->add_lines( grid->lines2add() );
  }
}

void Game::render_game( void )
{
  if (game_mode == GAME_TITLE )
  {
    //apply_surface( 0, 0, title_img, screen_img, NULL );
    apply_texture(title_img, NULL, renderer, 0, 0);
    if (menu_mode == TITLE_NEW){
      //apply_surface( TITLE_NEW_X, TITLE_NEW_Y, cursor_img, screen_img, NULL);
      apply_texture( cursor_img, NULL, renderer, TITLE_NEW_X, TITLE_NEW_Y);
    }
    else if (menu_mode == TITLE_ABOUT){
      //apply_surface( TITLE_ABOUT_X, TITLE_ABOUT_Y, cursor_img, screen_img, NULL);
      apply_texture( cursor_img, NULL, renderer, TITLE_ABOUT_X,TITLE_ABOUT_Y);
    }
  }    
  else if (game_mode == GAME_PLAY )
  {
    //apply_surface( 0,0, back_img, screen_img, NULL );
    apply_texture(back_img, NULL, renderer, 0, 0);
    //grid->render( screen_img );	//check this
    grid->render( renderer );	
    render_HUD();
  }      
  else if (game_mode == GAME_PAUSE )
  {
    //apply_surface( 0,0, back_img, screen_img, NULL );
    apply_texture( back_img, NULL, renderer, 0, 0);
    //grid->render(screen_img);
    grid->render(renderer);
    render_HUD();
  }    
  else if (game_mode == GAME_OVER )
  {
    //apply_surface( 0,0, back_img, screen_img, NULL );
    apply_texture(back_img, NULL, renderer,0,0);
    //render a game over message, wait 5 seconds, then change game_mode to GAME_TITLE
    //grid->render( screen_img );
    grid->render(renderer);
    render_HUD();
    timer->delay(DELAY_GAMEOVER);
    grid->reset_grid();
    level->reset();
    game_mode = GAME_TITLE;
    menu_mode = TITLE_NEW;

  }    
  else if (game_mode == GAME_ABOUT )
  {
    //apply_surface( 0, 0, about_img, screen_img, NULL );
    apply_texture(about_img, NULL, renderer, 0, 0);
  }

}

void Game::render_HUD( void )
{
  std::stringstream tmp; 
  
  tmp << "Level " <<  level->get_lvl();
  //tmp_msg = TTF_RenderText_Solid( font, tmp.str().c_str(), textColor );
  //apply_surface( MSG_LVL_XPOS, MSG_LVL_YPOS, tmp_msg, screen_img, NULL );
  tmp_msg = render_text(font, tmp.str().c_str(), textColor, renderer);
  apply_texture( tmp_msg, NULL, renderer, MSG_LVL_XPOS, MSG_LVL_YPOS);
  
  tmp.str(std::string());
  tmp.clear();
  tmp << "Lines " << level->get_lines();
  //tmp_msg = TTF_RenderText_Solid( font, tmp.str().c_str(), textColor );
  //apply_surface( MSG_LINES_XPOS, MSG_LINES_YPOS, tmp_msg, screen_img, NULL );
  tmp_msg = render_text( font, tmp.str().c_str(), textColor, renderer);
  apply_texture( tmp_msg, NULL, renderer, MSG_LINES_XPOS, MSG_LINES_YPOS);
  
  tmp.str(std::string());
  tmp.clear();
  tmp << "Score " << level->get_score();
  //tmp_msg = TTF_RenderText_Solid( font, tmp.str().c_str(), textColor );
  //apply_surface( MSG_SCORE_XPOS, MSG_SCORE_YPOS, tmp_msg, screen_img, NULL );
  tmp_msg = render_text(font, tmp.str().c_str(), textColor, renderer );
  apply_texture( tmp_msg, NULL, renderer, MSG_SCORE_XPOS, MSG_SCORE_YPOS);
  
  //apply_surface( MSG_NEXT_XPOS, MSG_NEXT_YPOS, next_msg, screen_img, NULL );
  apply_texture( next_msg, NULL, renderer, MSG_NEXT_XPOS, MSG_NEXT_YPOS);
  if (game_mode == GAME_PAUSE ){
    //apply_surface( MSG_PAUSE_XPOS, MSG_PAUSE_YPOS, pause_msg, screen_img, NULL );
    apply_texture( pause_msg, NULL, renderer, MSG_PAUSE_XPOS, MSG_PAUSE_YPOS);
  }
   
  
}
