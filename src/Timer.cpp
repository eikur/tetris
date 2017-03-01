#include "Timer.h"

//constructor
Timer::Timer( void )
{
  reset();
}

void Timer::delay( int msec )
{
  SDL_Delay( msec );
}

void Timer::start( void )
{
  state_run 	= true;
  state_pause 	= false;
  
  start_ticks 	= SDL_GetTicks();
  pause_ticks 	= 0;
}

void Timer::pause( void )
{
  state_run 	= false;
  state_pause 	= true; 
  pause_ticks 	= SDL_GetTicks();
}

void Timer::resume( void )
{
  state_run = true; state_pause = false;
  start_ticks = start_ticks + (SDL_GetTicks() - pause_ticks);
  pause_ticks = 0;  
}

void Timer::reset( void )
{
  start_ticks 	= 0;
  pause_ticks 	= 0;
  state_run 	= false;
  state_pause 	= false; 
}

bool Timer::chrono( bool input_pause, int msec )
{
  drop_msec = msec;
  if ( input_pause && (state_run || state_pause) )
  {
      if (state_run)
	pause();
      else if (state_pause ) 
        resume();
      return false;
  }
  if (!input_pause)
  {
    if (!state_run && !state_pause)
    {
      start(); return false;
    }
    // if it's started AND not paused  
    else if ( state_run && !state_pause && ((SDL_GetTicks() - start_ticks) >= drop_msec) )
    {
      reset();
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool Timer::get_state_run( void )
{
  return state_run;  
}

