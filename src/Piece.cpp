#include "Piece.h"

Piece::Piece( int piece ){
  tl_row = 0; 
  tl_col = 3; 
  rotation = 0;    
  for(int k=0;k<4;k++) 
    for (int i=0;i<4;i++) 
      for(int j=0;j<4;j++) 
	shape[k][i][j] = 0;
	
  if (piece == TETRIS_O)
  {
    shape[0][0][1] = TETRIS_O; shape[0][0][2] = TETRIS_O; shape[0][1][1] = TETRIS_O; shape[0][1][2] = TETRIS_O;
    shape[1][0][1] = TETRIS_O; shape[1][0][2] = TETRIS_O; shape[1][1][1] = TETRIS_O; shape[1][1][2] = TETRIS_O;
    shape[2][0][1] = TETRIS_O; shape[2][0][2] = TETRIS_O; shape[2][1][1] = TETRIS_O; shape[2][1][2] = TETRIS_O;
    shape[3][0][1] = TETRIS_O; shape[3][0][2] = TETRIS_O; shape[3][1][1] = TETRIS_O; shape[3][1][2] = TETRIS_O;
  }
  else if (piece == TETRIS_Z)
  {
    shape[0][0][0] = TETRIS_Z; shape[0][0][1] = TETRIS_Z; shape[0][1][1] = TETRIS_Z; shape[0][1][2] = TETRIS_Z;
    shape[1][0][2] = TETRIS_Z; shape[1][1][1] = TETRIS_Z; shape[1][1][2] = TETRIS_Z; shape[1][2][1] = TETRIS_Z;
    shape[2][0][0] = TETRIS_Z; shape[2][0][1] = TETRIS_Z; shape[2][1][1] = TETRIS_Z; shape[2][1][2] = TETRIS_Z;
    shape[3][0][2] = TETRIS_Z; shape[3][1][1] = TETRIS_Z; shape[3][1][2] = TETRIS_Z; shape[3][2][1] = TETRIS_Z;
  }
  else if (piece == TETRIS_S)
  {
    shape[0][0][1] = TETRIS_S; shape[0][0][2] = TETRIS_S; shape[0][1][0] = TETRIS_S; shape[0][1][1] = TETRIS_S;
    shape[1][0][1] = TETRIS_S; shape[1][1][1] = TETRIS_S; shape[1][1][2] = TETRIS_S; shape[1][2][2] = TETRIS_S;
    shape[2][0][1] = TETRIS_S; shape[2][0][2] = TETRIS_S; shape[2][1][0] = TETRIS_S; shape[2][1][1] = TETRIS_S;
    shape[3][0][1] = TETRIS_S; shape[3][1][1] = TETRIS_S; shape[3][1][2] = TETRIS_S; shape[3][2][2] = TETRIS_S;
  }
  else if (piece == TETRIS_T)
  {
    shape[0][0][1] = TETRIS_T; shape[0][1][0] = TETRIS_T; shape[0][1][1] = TETRIS_T; shape[0][1][2] = TETRIS_T;
    shape[1][0][1] = TETRIS_T; shape[1][1][1] = TETRIS_T; shape[1][1][2] = TETRIS_T; shape[1][2][1] = TETRIS_T;
    shape[2][1][0] = TETRIS_T; shape[2][1][1] = TETRIS_T; shape[2][1][2] = TETRIS_T; shape[2][2][1] = TETRIS_T;
    shape[3][0][1] = TETRIS_T; shape[3][1][0] = TETRIS_T; shape[3][1][1] = TETRIS_T; shape[3][2][1] = TETRIS_T;   
  }
  else if (piece == TETRIS_J)
  {
    shape[0][0][2] = TETRIS_J; shape[0][1][2] = TETRIS_J; shape[0][2][1] = TETRIS_J; shape[0][2][2] = TETRIS_J;
    shape[1][0][0] = TETRIS_J; shape[1][1][0] = TETRIS_J; shape[1][1][1] = TETRIS_J; shape[1][1][2] = TETRIS_J;
    shape[2][0][1] = TETRIS_J; shape[2][0][2] = TETRIS_J; shape[2][1][1] = TETRIS_J; shape[2][2][1] = TETRIS_J;
    shape[3][0][0] = TETRIS_J; shape[3][0][1] = TETRIS_J; shape[3][0][2] = TETRIS_J; shape[3][1][2] = TETRIS_J;       
  }
  else if (piece == TETRIS_L)
  {
    shape[0][0][1] = TETRIS_L; shape[0][1][1] = TETRIS_L; shape[0][2][1] = TETRIS_L; shape[0][2][2] = TETRIS_L;
    shape[1][0][0] = TETRIS_L; shape[1][0][1] = TETRIS_L; shape[1][0][2] = TETRIS_L; shape[1][1][0] = TETRIS_L;
    shape[2][0][1] = TETRIS_L; shape[2][0][2] = TETRIS_L; shape[2][1][2] = TETRIS_L; shape[2][2][2] = TETRIS_L;
    shape[3][0][2] = TETRIS_L; shape[3][1][0] = TETRIS_L; shape[3][1][1] = TETRIS_L; shape[3][1][2] = TETRIS_L; 
  }
  else if (piece == TETRIS_I)
  {
    shape[0][0][0] = TETRIS_I; shape[0][0][1] = TETRIS_I; shape[0][0][2] = TETRIS_I; shape[0][0][3] = TETRIS_I;
    shape[1][0][1] = TETRIS_I; shape[1][1][1] = TETRIS_I; shape[1][2][1] = TETRIS_I; shape[1][3][1] = TETRIS_I;
    shape[2][0][0] = TETRIS_I; shape[2][0][1] = TETRIS_I; shape[2][0][2] = TETRIS_I; shape[2][0][3] = TETRIS_I;
    shape[3][0][1] = TETRIS_I; shape[3][1][1] = TETRIS_I; shape[3][2][1] = TETRIS_I; shape[3][3][1] = TETRIS_I;     
  }
}


