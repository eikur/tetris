#include "constants.h"
class Level
{
private:
  int lvl;
  int num_lines;
  double score;
  int lvl_limit[9];	// no usamos el 0
  int lvl_speed[10];	//no usamos el 0 
  
  
  void update_lvl( void );
  
public: 
  Level( void );
  void reset( void );
  void add_lines( int );
  int get_lines( void );
  int get_speed( void );
  int get_lvl( void );
  double get_score( void );

};
