#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "title.h"
#include "SDL_ttf.h"
#include "simple_logger.h"

extern  SDL_Renderer* g_renderer;
int ShowTitle()
{
	SDL_RenderClear(g_renderer);


TTF_Font *font =  NULL;
TTF_Font *font2 =  NULL;
TTF_Font *font3 =  NULL;

font3 =	TTF_OpenFont( "fzero.ttf", 36 );
font2 =	TTF_OpenFont( "grandjean_types.ttf", 36 );
font  =	TTF_OpenFont( "IMFeDPit28P.ttf", 36 );

SDL_Rect Logo;

SDL_Texture* Title;
SDL_Texture* Title2;
SDL_Texture* Title3;
  if( font == NULL || font2 == NULL || font3 == NULL )
    {
     slog("font not loaded properly");
		return 0;
    }


  char title[32];
  char title2[32];
  char title3[32];
  strcpy(title ,"Capulet");
  strcpy(title2 ,"Mode");
  strcpy(title3 ,"Racing");
  SDL_Color textColor = { 255, 255, 255 };
  SDL_Color textColor2 = { 255, 22, 60 };
  SDL_Color textColor3 = { 55, 255, 50 };

  SDL_Surface *message = TTF_RenderText_Solid( font, title, textColor);
  SDL_Surface *message2 = TTF_RenderText_Solid( font2, title2, textColor2);
  SDL_Surface *message3 = TTF_RenderText_Solid( font2, title3, textColor3);


  Title = SDL_CreateTextureFromSurface( g_renderer, message );
  Title2 = SDL_CreateTextureFromSurface( g_renderer, message2 );
  Title3 = SDL_CreateTextureFromSurface( g_renderer, message3 );
		
  int done = 0;

  do  {


  Logo.x = 150;
  Logo.y = 150;
  Logo.w = 512;
  Logo.h = 128;
  	
    SDL_RenderCopy(g_renderer,Title,NULL,&Logo);
    Logo.w = 256;
    Logo.h = 128;
	Logo.x += 512;  
	SDL_RenderCopy(g_renderer,Title2,NULL,&Logo);  
	Logo.x -= 260;
	Logo.y += 128;
	SDL_RenderCopy(g_renderer,Title3,NULL,&Logo);  

	SDL_RenderPresent(g_renderer);
	
	SDL_Event e;
	 SDL_PollEvent( &e ); 
	
	if( e.type == SDL_KEYUP )
					{
						
				done = 1;

					}

}while(!done);// end do

  return 0;
}