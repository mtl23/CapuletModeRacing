 #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <chipmunk.h>
#include "SDL.h"
#include "SDL_image.h"
#include "sprite.h"
#include "SDL_ttf.h"
#include "graphics.h"
#include "bg.h"
#include "simple_logger.h"
#include "SDL_mixer.h" 
#include "title.h"
#include "entity.h"
#include "vector.h"
#include "glib.h"
#include "jansson.h"   
#include "car.h"   
#include "camera.h"
#include "physics.h"


extern int entityMax;

 int WINDOW_WIDTH = 1024;
 int WINDOW_HEIGHT = 768;
 SDL_Window* g_mainWindow;
 SDL_Renderer* g_renderer;
 SDL_Event g_e;
 

/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
  int done = 0;// the player
  const Uint8 *keys;// the player
  //// Create an empty space, a chipmunk test. THIS IS OUR INIT PHYSICS
   
  cpSpace *g_space = NULL;
  g_space = InitPhysicsSystem();
 
  ////FOR EACH CAR ENTITY////
  int boxSize = 1;
  int boxMass = 1;
  cpFloat radius = cpvlength(cpv(boxSize, boxSize));

  cpBody *boxBody = cpSpaceAddBody(g_space, cpBodyNew(boxMass, cpMomentForBox(boxMass, boxSize, boxSize)));
  cpShape *boxShape = cpSpaceAddShape(g_space, cpBoxShapeNew(boxBody, boxSize, boxSize, 0.0));
  cpShapeSetElasticity(boxShape, 0.0f);
  cpShapeSetFriction(boxShape, 0.7f);
 
  cpVect startPos = cpv(450 , 340);// set the starting position in chipmunk coordinates
  cpBodySetPosition(boxBody,startPos);
  
   
   ////FOR EACH CAR ENTITY////

  //// Create an json interger, a json test.
 json_int_t x = 123123123;
 printf("x is % " JSON_INTEGER_FORMAT "\n", x);
 ///SDL with chipmunk to draw the box
 Sprite_M boxSprite;


//create a Gstring and print it, a glib test
 Vector2D Init_car_position;
 Init_car_position.x = 450;
 Init_car_position.y = 340;
GString *mat;
mat = g_string_new ("Chipmunk, Jasson, and ");
g_string_append_printf(mat,"Glib all tested and working\nThanks"); 

printf("%s",mat->str);


///////////////////////////////////////////////////////////////////////////////////////////////////
SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &g_mainWindow, &g_renderer);
SDL_SetWindowTitle(g_mainWindow, "Capulet Mode");
 if( TTF_Init() == -1 )
	{
		return false;    
	}

  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return false;  
  }

  /////////////////////////////////////////////////////////////////////////////////
	Mix_Music *menu_music;
	menu_music = Mix_LoadMUS( "sfx/Theme.WAV" );
	Mix_Music *demo_music;
	demo_music = Mix_LoadMUS( "sfx/surf.mid" );
	
	InitSpriteSystem();
	InitEntitySystem(entityMax);
	
	if( Mix_PlayingMusic() == 0 )
					{
						//Play the music
						if( Mix_PlayMusic( menu_music, -1 ) == -1 )
						{
							return 1;
						} 
					}
	ShowTitle();
	Mix_PlayMusic( demo_music, -1 );
	Sprite_M BG1;
	Car_M p1car;
	mat->str = "images/car.png";
	p1car = newPlayerCar(mat, 1, Init_car_position.x, Init_car_position.y, 128, 128, g_space);
	BG1 = *spriteLoad("images/m7_map.png",256,256);
	camera_M MyCam = newCamera(BG1);


	/*TODO
	
	Refactor the entity system to make use of chipmunk intergaration.
	
	*/

	int testBoxSize = 128;
	SDL_Rect* chipmunkBox = new SDL_Rect();

	chipmunkBox->h = testBoxSize;
	chipmunkBox->w = testBoxSize;


	/////////////////////EZ OBSTACLES TO BE REFACTORED TO OBSTACLE CLASS/////////////////////////
	
	//IMPLEMENTATION #1
	
	/*Car_M p0car;
	mat->str = "images/block.png";
	p0car = newCarObstacle(mat, 1, 450, 390, 32, 32);

	Car_M p2car;
	mat->str = "images/block.png";
	p2car = newCarObstacle(mat, 1, 550, 200, 64, 64);

	Car_M p3car;
	mat->str = "images/block.png";
	p3car = newCarObstacle(mat, 1,330, 330,64,64);*/
/*
	Car_M p4car;
	mat->str = "images/block.png";
	p4car = newCarObstacle(mat, 1, 500, 275,64,64);*/
	///////////////////IMPLEMENTATION #2/////////////////////////////

	//Entity_S* Moo = EntityNew();
	//Moo->position.x = 550;
	//Moo->position.y = 450;
	//Moo->size.x = 256;
	//Moo->size.y = 256;
	//Moo->sprite = spriteLoad("images/redblock.png", 256, 256);
	//Moo->sprite->angle = 270.0f;
	//Moo->draw = &drawPlayerCar;	
	//////////END EZ OBSTACLES TO BE REFACTORED TO OBSTACLE CLASS///////////////////
	
	
	float invertYpos;
	float xPos_offset = 0;
	float yPos_offset = 0;
	do
	{
	SDL_RenderClear(g_renderer);	
	DrawBG(BG1, MyCam);	


	/*TO DO 
	
	
	REFACTOR BELOW CODE TO THE CAR.C LOGIC IN EITHER THINK OR DRAW, CHANGE FUNCTION SIGNMATURES AS NECESSARY 

	YOU WILL NEED 'BOXBODY', WINDOOW_HEIGHT,
	
	
	*/

	//// chipmunk box's current position
	cpVect NewBoxCoordinates = cpBodyGetPosition(boxBody); // get new coordinates of the body


	//THIS SECTION GOES IN THINK

	////-Shift the x and y by 1 / 2 the width and height of your object
	////xPos_offset = (testBoxSize / 2);
	////yPos_offset = (testBoxSize / 2);
	chipmunkBox->x = (NewBoxCoordinates.x);//// +xPos_offset;  // update x pos to the sdl box
	chipmunkBox->y = (NewBoxCoordinates.y);//// +yPos_offset;
	invertYpos =  WINDOW_HEIGHT - chipmunkBox->y;
	////  update y pos for sdl box with necessary conversion [- Invert the Y (e.g. invert_pos_y = SCREEN_HEIGHT - chipmunk_pos.y)]
	chipmunkBox->y = invertYpos;


	//THIS SECTION GOES IN DRAW
	SDL_SetRenderDrawColor(g_renderer,0,0,255,0);////blue box buy default;
	SDL_RenderDrawRect(g_renderer, chipmunkBox); ////  send it to the renderer
	////chipmunk box
	////- Convert radians to degrees (chipmunk_angle * (360.0 / (2 * PI))
	////-flip the sign of the angle

	

	entityThinkAll();
	entityDrawAll();
	//for testing only, ovverride the loop logic to draw thw test car in the chipmunk simuation
	p1car.car->position.x = chipmunkBox->x;
	p1car.car->position.y = chipmunkBox->y;

	//TEST TO SEE IF COORDINATES OF THE BOX AND SPRITE ARE THE SAME.
	//slog(("This is the position of the  box X:%d,Y:%d"), chipmunkBox->x, chipmunkBox->y);
	//slog(("This is the position of the  sprite X:%f,Y:%f"), p1car.car->position.x, p1car.car->position.y);
	

		if(&g_e)
					{
				
					//User presses a key
					if( g_e.type == SDL_KEYDOWN )
					{
						
						
						//Select surfaces based on key press
						switch( g_e.key.keysym.sym )
						{
						
							case SDLK_RETURN :
						{
						//slog("return is down");	
						g_e.type = SDLK_CLEAR;
						break;
						}
						}// end switch
					}//end if if( e.type == SDL_KEYDOWN )
					}//end 	if(&e)
	
	keys = SDL_GetKeyboardState(NULL);

	if(keys[SDL_SCANCODE_ESCAPE])
	{
		
		done = 1;
	}
	
		NextFrame();
		cpSpaceStep(g_space, 1.0f/60.0f);

	}while(!done);

	//FREE UP EVERYTHING HERE
  
	SDL_DestroyRenderer( g_renderer );
	SDL_DestroyWindow( g_mainWindow );
	g_renderer = NULL;
	 g_mainWindow = NULL;
	spriteFree(&BG1);	
	
	entityFreeAll();
	Mix_FreeMusic(menu_music);
	menu_music=NULL; // so we know we freed it...
	Mix_FreeMusic(demo_music);
	demo_music=NULL; // so we know we freed it...
  exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/ 
 return 0;
}
