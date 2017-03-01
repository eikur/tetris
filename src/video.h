#pragma once
#include "constants.h"

/* Cargar imágenes*/
SDL_Texture* load_image( std::string, SDL_Renderer*);

/*Render text */
SDL_Texture* render_text( TTF_Font*, const char*, SDL_Color, SDL_Renderer* );

/* superponer superfícies */
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip );

/*superponer texturas*/
void apply_texture( SDL_Texture*, SDL_Rect*, SDL_Renderer*, int, int);
/*iniciar sistemas*/
bool init (void);
