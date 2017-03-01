#include "Grid.h"

Grid::Grid( SDL_Renderer *rndrr){
  renderer = rndrr;
  // LOGIC grid
  grid = new int[GRID_COL*GRID_ROW];
  
  reset_grid();
  // GRAPHIC grid
  //layout = load_image( GRID_IMAGE );
  layout = load_image( GRID_IMAGE, renderer );
  //blocks = load_image( BLOCKS_IMAGE );
  blocks = load_image( BLOCKS_IMAGE, renderer );
  // CLIPS
  bclip = new SDL_Rect[7];
  for (int i = 0; i< 7; i++ )
  { 
    bclip[i].x = i*TILE_PIXEL; 	bclip[i].y = 0;
    bclip[i].w = TILE_PIXEL; 	bclip[i].h = TILE_PIXEL;
  }
 
   // random generator :)
   srand( time(NULL) );
   next_piece();
   spawn_piece();
   
}

Grid::~Grid(){
 delete grid;
 delete bclip;
}

void Grid::reset_grid()
{
  for (int j = 0; j< GRID_ROW*GRID_COL; j++)
      grid[ j ] = 0;
  gameover = false; 
  lines = 0;
}

void Grid::update( int key )
{
  if (key == KEY_LEFT)
    move_left();
  else if (key == KEY_RIGHT )
    move_right();  
  else if (key == KEY_UP)
    rotate();
  else if (key == KEY_DOWN)
    move_down();
}

void Grid::move_left( void )
{
  int i, j;
  int result = 0;
  
  piece->new_tl_col = piece->tl_col -1;
  piece->new_tl_row = piece->tl_row;
 
  if (piece->new_tl_col < GRID_LEFT_COL) //out of bounds!
  {
    for ( i=0; i<4; i++)	// si la pieza tiene bloques , result >0
      result += piece->shape[piece->rotation][i][GRID_LEFT_COL-piece->new_tl_col-1];
    if (result == 0)		//si no la tiene, miramos que no haya colision
    {
      for( i = 0; i < 4; i++)
	for (j = 1; j < 4; j++ )
	  result += piece->shape[piece->rotation][i][j] * grid[ IDC2D( piece->new_tl_row + i, piece->new_tl_col + j) ];
    }
  }
  else if (piece->new_tl_col >= GRID_LEFT_COL) 
  {
    for( i = 0; i < 4; i++)
      for (j = 0; j < 4; j++ )
	result += piece->shape[piece->rotation][i][j] * grid[ IDC2D( piece->new_tl_row + i, piece->new_tl_col + j) ];
  }
  if (result == 0 )
  {
    piece->tl_col = piece->new_tl_col;
    piece->tl_row = piece->new_tl_row;
  }
 }

void Grid::move_right( void )
{
  int i, j;
  int result = 0;
  
  piece->new_tl_col = piece->tl_col + 1;
  piece->new_tl_row = piece->tl_row;
  
  if (piece->new_tl_col >= 7) // && piece->new_tl_col < 9){	//topleft + 3 == 9 :)
   {
    for ( i=0; i<4; i++)
      result += piece->shape[piece->rotation][i][GRID_COL-piece->new_tl_col];
    if (result == 0)
    {
      for( i = 0; i < 4; i++)
	for (j = 0; j < GRID_COL - piece->new_tl_col; j++ )
	  result += piece->shape[piece->rotation][i][j] * grid[ IDC2D( piece->tl_row + i, piece->new_tl_col + j) ];
    }
  }
  else if (piece->new_tl_col < 7)
  {
    for( i = 0; i < 4; i++)
      for (j = 0; j < 4; j++ )
	result += piece->shape[piece->rotation][i][j] * grid[ IDC2D( piece->tl_row + i, piece->new_tl_col + j) ]; 
  }
  if (result == 0 )
  {
    piece->tl_col = piece->new_tl_col;
    piece->tl_row = piece->new_tl_row;
  }
}


void Grid::move_down( void )
{
  int row,col;
  int result = 0;
  int c_start = 0;
  int c_end = 3;
  
  piece->new_tl_col = piece->tl_col;
  piece->new_tl_row = piece->tl_row + 1;

    if (piece->new_tl_col < GRID_LEFT_COL )
      c_start = GRID_LEFT_COL-piece->new_tl_col;	
    else if (piece-> new_tl_col +3 > GRID_RIGHT_COL)
      c_end = GRID_RIGHT_COL - piece->new_tl_col;
 
  if (piece->new_tl_row + 3 > GRID_BOTTOM_ROW) // hay una parte del bloque que se escapa
  {
    for ( col = c_start; col <= c_end ; col++)
       result += piece->shape[piece->rotation][GRID_BOTTOM_ROW - piece->new_tl_row + 1][col];
    if (result == 0)
    {
      for( row = 0; row < 4; row++)
	for (col = c_start; col <= c_end; col++ )
	  result += piece->shape[piece->rotation][row][col] * grid[ IDC2D( piece->new_tl_row + row, piece->new_tl_col + col) ];          
    }
  }
  else if (piece->new_tl_row + 3 <= GRID_BOTTOM_ROW) //no se escapa ningun bloque
  {
    for( row = 0; row < 4; row++)
      for (col = c_start; col <= c_end; col++ )
	result += piece->shape[piece->rotation][row][col] * grid[ IDC2D( piece->new_tl_row + row, piece->new_tl_col + col) ];    
  }
  if (result == 0)
  {
    piece->tl_row = piece->new_tl_row;
    piece->tl_col = piece->new_tl_col;
  }
  else
  {
     copy2grid( );
     if (!gameover)
     {
      check_lines();
      delete piece; delete preview;
      spawn_piece();
     }
  }
}


void Grid::rotate( void )
{
  int row,col;
  int result = 0;
  int result2 = 0; // for right side wall kick
  int c_start = 0;
  int c_end = 3;
  int r_start = 0;
  int r_end = 3;

  piece->new_rotation = (piece->rotation + 1) %4; 
  //TPO
  piece->new_tl_row = piece->tl_row;
  piece->new_tl_col = piece->tl_col;
  
  if (piece->tl_col < GRID_LEFT_COL ) 
  {
    for (row = 0; row < 4; row++)
      result += piece->shape[piece->new_rotation][row][0];

    if (result == 0){
      piece->new_tl_col = piece->tl_col; 
      piece->new_tl_row = piece->tl_row;      
      c_start = GRID_LEFT_COL-piece->tl_col;
    }
    else {
      piece->new_tl_col = piece->tl_col + 1; 
      piece->new_tl_row = piece->tl_row; 
      c_start = 0;
    } 
  }

  else if ( piece->tl_col + 3 == GRID_RIGHT_COL + 1 ) // piece->tl_col == 7
  {
    for (row = 0; row < 4; row++)
      result += piece->shape[piece->new_rotation][row][3];
    
    if (result == 0){
      piece->new_tl_col = piece->tl_col; 
      piece->new_tl_row = piece->tl_row;      
      c_end = 2;
    }
    else {
      piece->new_tl_col = piece->tl_col -1; 
      piece->new_tl_row = piece->tl_row; 
      c_end = 3;
    } 

  }
  else if (piece->tl_col + 3 == GRID_RIGHT_COL + 2)  // piece->tl_col == 8
  {
    for (row = 0; row < 4; row++){
      for (col = 2; col < 4; col++){
	result += piece->shape[piece->new_rotation][row][col];    
	result2 += piece->shape[piece->new_rotation][row][3];
      }
    }
    if (result == 0){
      piece->new_tl_col = piece->tl_col; 
      piece->new_tl_row = piece->tl_row;      
      c_end = 1;
    }
    else {
      if (result2 == 0)
	piece->new_tl_col = piece->tl_col -1; 
      else
	piece->new_tl_col = piece->tl_col -2; 
      piece->new_tl_row = piece->tl_row; 
      c_end = 3;
    } 
  }
  else if (piece->tl_row + 3 == GRID_BOTTOM_ROW +1 )
  {
    for (col = 0; col < 4; col++)
      result += piece->shape[piece->new_rotation][3][col];
    
    if (result == 0){
      piece->new_tl_col = piece->tl_col; 
      piece->new_tl_row = piece->tl_row;      
      r_end = 2;
    }
    else {
      piece->new_tl_col = piece->tl_col; 
      piece->new_tl_row = piece->tl_row - 1; 
      r_end = 3;   
    }
  }
  else if (piece->tl_row + 3 == GRID_BOTTOM_ROW +2 )
  {
    for (col = 0; col < 4; col++){
      for (row = 2; row < 4; row++){
	result += piece->shape[piece->new_rotation][row][col];
	result2 += piece->shape[piece->new_rotation][3][col];
      }
    }
    
    if (result == 0){
      piece->new_tl_col = piece->tl_col; 
      piece->new_tl_row = piece->tl_row;      
      r_end = 2;
    }
    else {
      piece->new_tl_col = piece->tl_col;
      if (result2 == 0)
	piece->new_tl_row = piece->tl_row - 1; 
      else
	piece->new_tl_row = piece->tl_row -2;
      r_end = 3;    
    }    
  }
  //collision check
  result = 0;
  for( row = c_start; row <= r_end; row++)
    for (col = c_start; col <= c_end; col++ )
      result += piece->shape[piece->new_rotation][row][col] * grid[ IDC2D( piece->tl_row + row, piece->tl_col + col) ];            
    
  if (result == 0 )
  {
    piece->rotation = piece->new_rotation;
    piece->tl_col = piece->new_tl_col;
    piece->tl_row = piece->new_tl_row; 
  }
}

//copy and check
void Grid::copy2grid( void )
{
  int i, j, value, result; 
  for( i = 0; i < 4; i++){
    for(j=0;j<4;j++){
      value = piece->shape[piece->rotation][i][j];
      if (value!=0){
	result += grid[ IDC2D(i + piece->tl_row,j + piece->tl_col) ];	
	grid[ IDC2D(i + piece->tl_row,j + piece->tl_col) ] = value;
      }
    }
  }
  if (result > 0 && piece->tl_row == 0)
    gameover = true; 
}

void Grid::check_lines( void )
{
  int row, col;
  int add, mult;
  bool loop = true;
  int n = 0;
  int del[4] = {-1,-1,-1,-1};
  
  for (row = GRID_BOTTOM_ROW; row >= GRID_TOP_ROW; row--){
    add = 0; mult = 1;
    for (col = GRID_LEFT_COL; col <= GRID_RIGHT_COL; col++){
      add += grid[ IDC2D( row, col)];
      mult *= grid[IDC2D( row, col)];
    }
    if (add == 0)	//linea vacía -> no seguimos
      loop = false;
    else if (mult != 0) // linea llena
      del[n++] = row;
  }
  if (n>0)
    clear_line( del );
}

void Grid::clear_line( int *rows )
{
  int row;
  int r,c;
  int i;
  int count = 0;
  //int tmp;
  int deleted = 0;
  bool found;
  //marcamos la primera componente de la línea para su borrado
  for (i=3; i >=0; i--){
    if( rows[i] != -1 ){
      grid[ IDC2D( rows[i], 0 )] = -1;    
      count++;
    }
  }
  lines = count;
  //eliminamos las lineas marcadas 
  for (deleted = 0; deleted < count; deleted++ )
  {
    found = false;
    for (row = GRID_BOTTOM_ROW; (row >= (GRID_TOP_ROW + count)) && !found; row--){
      if ( grid[ IDC2D( row, 0 )] == -1)
      {
	found = true;
	for (r = row; r > GRID_TOP_ROW; r--)
	  for (c = GRID_LEFT_COL; c <= GRID_RIGHT_COL; c++)
	    grid[ IDC2D(r,c)] = grid[IDC2D(r-1,c)];
      }
    }
  }
}

int Grid::lines2add( void )
{
  int tmp = lines; 
  lines = 0;
  return tmp;  
}

//void Grid::render( SDL_Surface *destination )
void Grid::render( SDL_Renderer *renderer )
{
  //apply background
  //apply_surface( GRID_LAY_XPOS, GRID_LAY_YPOS, layout, destination, NULL);  
  apply_texture( layout, NULL, renderer, GRID_LAY_XPOS, GRID_LAY_YPOS);
 
  //apply fallen blocks
  int value;
  int preview_value;
  int i, j;
  for (j = GRID_COL-1; j >= 0; j--)
  {
    for (i = GRID_ROW-1; i >= 0; i--)
    {  
      value = grid[ IDC2D(i,j) ]; 
      if (value !=0)
      {
	//apply_surface( XPOS_L(j), YPOS_L(i), blocks, destination, &bclip[value-1]);
	apply_texture( blocks, &bclip[value-1],renderer, XPOS_L(j), YPOS_L(i));
      }
    }
  }
  // collision detection ALREADY DONE
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      value = piece->shape[piece->rotation][i][j];
      preview_value = preview->shape[0][i][j];
      if (value!=0)
      {
	//apply_surface( XPOS_F(j,piece->tl_col), YPOS_F(i,piece->tl_row), blocks, destination, &bclip[value-1]);
	apply_texture( blocks, &bclip[value-1], renderer, XPOS_F(j,piece->tl_col), YPOS_F(i,piece->tl_row));
      }
      if (preview_value != 0)
      {
	//apply_surface( XPOS_P(j), YPOS_P(i), blocks, destination, &bclip[preview_value-1]);
	apply_texture(blocks, &bclip[preview_value-1], renderer, XPOS_P(j), YPOS_P(i));
      }
    } 
  }

}

void Grid::next_piece( void )
{
  next = rand()%7 + 1;
}

void Grid::spawn_piece(void)
{
    piece = new Piece(next);
    next_piece();
    preview = new Piece(next);
}

bool Grid::is_gameover( void )
{
  return gameover;
}
