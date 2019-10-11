
#include "SDL.h"
#include "SDL_image.h"
#include "simple_logger.h"
#include "bg.h"
#include "sprite.h"
#include "camera.h"
extern    SDL_Renderer* g_renderer;

void DrawBG(Sprite_M bg1, camera_M cam )
{

SDL_RenderCopy(g_renderer, bg1.image,&cam.game_cam,NULL);
  
}