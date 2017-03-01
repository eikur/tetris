#include "video.h"

SDL_Texture* load_image( std::string filename, SDL_Renderer *renderer )
{
  SDL_Surface *loaded_surface = NULL;	
  SDL_Texture *texture = NULL;	
  loaded_surface = IMG_Load( filename.c_str() );
  if (loaded_surface != NULL )			
  {
    texture = SDL_CreateTextureFromSurface( renderer, loaded_surface);
      SDL_FreeSurface( loaded_surface);
      if (texture == NULL){
	std::cout << "Unable to create texture from " << filename << std::endl;
	std::cout << "SDL Error : " << SDL_GetError() << std::endl;
	return NULL;	// something wrong with the texture conversion	
      }
      else{
	return texture;
      }
  }
  else{
    std::cout << "Unable to create texture from " << filename << std::endl;
    std::cout << "SDL Error : " << SDL_GetError() << std::endl;
    return NULL;  	// nothing loaded
  }
}

SDL_Texture* render_text( TTF_Font* font, const char* message, SDL_Color color, SDL_Renderer *renderer)
{
  SDL_Surface *tmp = TTF_RenderText_Solid( font, message, color);
  SDL_Texture *texture = NULL;
  if (tmp == NULL){
    std::cout << "SDL Error : " << SDL_GetError() << std::endl;
    return NULL;
  }else{
    texture = SDL_CreateTextureFromSurface( renderer, tmp);
    if (texture == NULL)
      std::cout << "SDL Error : " << SDL_GetError() << std::endl;
    return texture;
  }
}

void apply_texture( SDL_Texture *sourceTexture, SDL_Rect *sourceClip, SDL_Renderer* renderer, int x, int y)
{
  int w, h;
  SDL_Rect destRect;
  SDL_QueryTexture(sourceTexture, NULL, NULL, &w, &h);
  if(sourceClip == NULL)
  {
    destRect.x = x; destRect.y = y; destRect.w = w; destRect.h = h;
  }
  else
  {
    destRect.x = x; destRect.y = y; destRect.w = sourceClip->w; destRect.h = sourceClip->h;
  }
  SDL_RenderCopy (renderer, sourceTexture, sourceClip, &destRect);
}

bool init (void)
{
  
  if (SDL_Init(  SDL_INIT_EVERYTHING ) == -1 )
    return false;
  if ( TTF_Init() == -1 )
    return false;
  return true;                      
}