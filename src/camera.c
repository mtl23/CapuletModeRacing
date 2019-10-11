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
#include "camera.h"
#include "jansson.h"   
#include "car.h"  

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

camera_M newCamera (Sprite_M Map)
{

camera_M Camcam; 

Camcam.think = &cameraThink;
SDL_Rect gameCamDefault = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
SDL_Rect worldCamDefault = {0,0,Map.frameW,Map.frameH}; 

Camcam.game_cam = gameCamDefault; 
Camcam.level_cam = worldCamDefault;


return Camcam;
}


void freeCamera()
{

}


void cameraThink(struct camera_M self,struct Entity_S car) // scroll speed moves more slowly than regular game loop
{
	/*self.game_cam.x = (car.position.x  - WINDOW_WIDTH);
	self.game_cam.y = (car.position.y  - WINDOW_HEIGHT);
 
	if(self.game_cam.x < 0)
	{
		self.game_cam.x = 0;
	}
	if(self.game_cam.y < 0)
	{
		self.game_cam.y = 0;
	}
	
	if(self.game_cam.x + self.game_cam.w >= self.level_cam.w )
	{
		self.game_cam.x = (self.level_cam.w - self.game_cam.w);
	
	}

	if(self.game_cam.y + self.game_cam.h >= self.level_cam.h)
	{
		self.game_cam.y = (self.level_cam.h - self.game_cam.h);
	}

	if(car.position.x > self.game_cam.w - self.level_cam.w)
	{
		car.velocity.x = 0;
		car.acceleration.x = 0;
	}


	if(car.position.y > self.level_cam.h)
	{
	 car.velocity.y = 0;
	 car.acceleration.y = 0;
	 }

	 	 if(car.position.x < 0)
	{
		car.velocity.x = 0;
		car.acceleration.x = 0;
	}
	 if(car.position.y < 0)
	{
		car.velocity.y = 0;
		car.acceleration.y = 0;
	}*/
}
