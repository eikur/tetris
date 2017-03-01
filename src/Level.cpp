#include "Level.h"

Level::Level( void )
{
  // speeds
  lvl_speed[0] = 0; //dummy
  lvl_speed[1] = LVL1SPD; 	lvl_speed[2] = LVL2SPD;		lvl_speed[3] = LVL3SPD;	
  lvl_speed[4] = LVL4SPD;	lvl_speed[5] = LVL5SPD;		lvl_speed[6] = LVL6SPD;
  lvl_speed[7] = LVL7SPD;	lvl_speed[8] = LVL8SPD;		lvl_speed[9] = LVL9SPD;
  //limits
  lvl_limit[0] = 0; //dummy
  lvl_limit[1] = LVL1LMT;	lvl_limit[2] = LVL2LMT;	 	lvl_limit[3] = LVL3LMT;	 	lvl_limit[4] = LVL4LMT;
  lvl_limit[5] = LVL5LMT;	lvl_limit[6] = LVL6LMT;	 	lvl_limit[7] = LVL7LMT;	 	lvl_limit[8] = LVL8LMT;
  
  reset();
}

void Level::reset( void )
{
  lvl = 1;   num_lines = 0;   score = 0;
}

//work to do :)
void Level::add_lines( int lines )
{
  if (lines!= 0)
  {
    num_lines +=lines;
    if (lines == 4)
      score += 1000;
    else if (lines ==3)
      score += 600;
    else if (lines == 2)
      score += 300;
    else
      score += 100;
    update_lvl();
  }
}

int Level::get_lines( void )
{
  return num_lines;
}

int Level::get_lvl( void )
{
return lvl;  
  
}

int Level::get_speed( void )
{
  return lvl_speed[lvl];
}

double Level::get_score( void )
{
  return score;
}

void Level::update_lvl( void )
{
  if (lvl< 9)
  {
    if (num_lines >= lvl_limit[lvl])
      lvl++;
  }
}
