#ifndef _CAMERA_
#define _CAMERA_

#include "SDL.h"
#include "SDL_image.h"
#include "Entity.h"

typedef struct camera_M
{
	
	void(*think) (struct camera_M self,struct Entity_S car); /**logic*<*/
	SDL_Rect game_cam;
	SDL_Rect level_cam;
	Vector2D position;
	

}camera_M;


camera_M newCamera(Sprite_M Map);
void freeCamera();

void DrawCamera();
void cameraThink(struct camera_M self,struct Entity_S car);
#endif