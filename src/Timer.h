#include "constants.h"

class Timer
{

private:
  int start_ticks;
  int pause_ticks;
  bool state_run;
  bool state_pause;
  int 	drop_msec;

public:
  Timer();
  void delay( int );
  void start( void);
  void pause( void );
  void resume( void );
  void reset( void );
  bool chrono( bool,int );
  bool get_state_run( void );
};
