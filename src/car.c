#include <SDL.h>
#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "sprite.h"
#include "glib.h"
#include "entity.h"
#include "simple_logger.h"
#include "car.h"

extern SDL_Renderer* renderer;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
Car_M newPlayerCar(GString *model, int type, float PosX, float PosY, float sizeX, float sizeY, cpSpace* g_space)// creates a player car entity with the path to the sprite needed.
{
	struct Car_M pcar;
	pcar.floaty =  5; 
	pcar.car = EntityNew();
	pcar.car->startPos.x = PosX;
	pcar.car->startPos.y = PosY;
	pcar.car->sprite = spriteLoad(model->str,128,128);
	pcar.type = 1;
	pcar.car->sprite->angle = 270;
	pcar.car->top_acl = .001;
	pcar.car->top_spd = .02;
	pcar.car->position.x = PosX;
	pcar.car->position.y = PosY;
	pcar.car->draw = &drawPlayerCar; //assign the car a pointer function to draw
	pcar.car->think = &thinkCar;
	pcar.car->size.x = sizeX;
	pcar.car->size.y = sizeY;
	//pcar.boxSize = 1;
	//pcar.boxMass = 1;
	//cpFloat radius = cpvlength(cpv(pcar.boxSize, pcar.boxSize));

	//cpBody *boxBody = cpSpaceAddBody(g_space, cpBodyNew(pcar.boxMass, cpMomentForBox(pcar.boxMass, pcar.boxSize, pcar.boxSize)));
	//cpShape *boxShape = cpSpaceAddShape(g_space, cpBoxShapeNew(boxBody, pcar.boxSize, pcar.boxSize, 0.0));
	//cpShapeSetElasticity(boxShape, 0.0f);
	//cpShapeSetFriction(boxShape, 0.7f);

	//cpVect startPos = cpv(450, 340);// set the starting position in chipmunk coordinates
	//cpBodySetPosition(boxBody, startPos);
	//
	pcar.car->chipmunkBox = new SDL_Rect();
	//pcar.car->chipmunkBox->x = pcar.car->startPos.x;
	//pcar.car->chipmunkBox->y = pcar.car->startPos.y;
	//pcar.car->chipmunkBox->w = sizeX;
	//pcar.car->chipmunkBox->h = sizeY;
	return pcar;
}

Car_M newCar(GString *model, int type, float PosX, float PosY,float sizeX, float sizeY)// creates a car entity with the path to the sprite needed.
{
	struct Car_M pcar;
	pcar.floaty = 5;
	pcar.car = EntityNew();
	pcar.car->sprite = spriteLoad(model->str, sizeX, sizeY);
	pcar.type = 1;
	pcar.car->sprite->angle = 270;
	pcar.car->top_acl = .001;
	pcar.car->top_spd = .02;
	pcar.car->position.x = PosX;
	pcar.car->position.y = PosY;
	pcar.car->draw = &drawPlayerCar; //assign the car a pointer function to draw
	pcar.car->think = &thinkCar; 
	pcar.car->size.x = sizeX;
	pcar.car->size.y = sizeY;

	return pcar;
}

Car_M newCarObstacle(GString *model, int type, float PosX, float PosY, float sizeX, float sizeY)// creates a car entity with the path to the sprite needed.
{
	struct Car_M pcar;
	pcar.floaty = 5;
	pcar.car = EntityNew();
	pcar.car->sprite = spriteLoad(model->str, sizeX, sizeY);
	pcar.type = 1;
	pcar.car->sprite->angle = 270;
	pcar.car->top_acl = .001;
	pcar.car->top_spd = .02;
	pcar.car->position.x = PosX;
	pcar.car->position.y = PosY;
	pcar.car->size.x = sizeX;
	pcar.car->size.y = sizeY;
	pcar.car->draw = &drawPlayerCar; //assign the car a pointer function to draw
	//pcar.car->think = &thinkCar;
	return pcar;
}
void SetCarPositon(Car_M car, Vector2D position)
{
	car.car->position.x = position.x;
	car.car->position.y = position.y;
	return;
}


void drawCar(struct Entity_S *self, SDL_Renderer *renderer) //Use for AIcars
{

}
void drawPlayerCar(struct Entity_S *self, SDL_Renderer *renderer) // used for the player's car
{
	Vector2D pos;
	pos.x = self->position.x;
	pos.y = self->position.y;
	Vector2D dim;
	dim.x = self->size.x;
	dim.y = self->size.y;
	spriteDraw(self->sprite, renderer, 0, dim, pos);
}
void thinkCar(struct Entity_S *self)

{
	float radians;
	float newTime; 
	float previousTime = 0;
	float dt;
	Vector2D dirVect;
	radians = self->sprite->angle*(M_PI/180);
	dirVect.x = cos(radians);
	dirVect.y = sin(radians);
	newTime= SDL_GetTicks();
	dt = previousTime - newTime;
	previousTime = SDL_GetTicks();
	dt=previousTime;
	

	
	self->velocity.y += self->acceleration.y;
	self->velocity.x += self->acceleration.x;

	self->position.x+= self->velocity.x;
	self->position.y+= self->velocity.y;

	/*TO DO
	
	Get car acceleration and velocity from chipmunk, and use here mtl23/9/29/2019
	 

	*/

	//slog("SPEED is %f %f", self->velocity.x, self->velocity.y);
	//slog("ACCEL.x is %f", self->acceleration.x);
	//slog("ACCEL.y is %f", self->acceleration.y);
	//slog ("Dir Y is %f", dirVect.y);

	if(self->velocity.x > 0 && self->velocity.x >self->top_spd )
	{
		//slog("CAP the speed X pos");
		self->velocity.x = self->top_spd;
	}

	 if(self->velocity.x < 0 && self->velocity.x < -1*(self->top_spd) )
	{
		//slog("CAP the speed X neg");
		self->velocity.x = (self->top_spd)*-1;
	}


	if(self->velocity.y > 0 && self->velocity.y >self->top_spd )
	{
		//slog("CAP the speed Y pos");
		self->velocity.y = self->top_spd;
	}

	 if(self->velocity.y < 0 && self->velocity.y < -1*(self->top_spd) )
	{
	//	slog("CAP the speed Y neg" );
		self->velocity.y = (self->top_spd)*-1;
	}

	 ////Wrap the car around the screen for the time being///
	 if (self->position.x>WINDOW_WIDTH + self->sprite->frameW) //car has gone too far right 
	 {
		 self->position.x = 0;
	 }
 
	 if (self->position.x<0 - self->sprite->frameW) //car has gone too far left 
	 {
		 self->position.x = WINDOW_WIDTH - self->sprite->frameW;
	 }

	 if (self->position.y<0 - self->sprite->frameH) //car has gone too far up 
	 {
		 self->position.y = WINDOW_HEIGHT - self->sprite->frameH;
	 }

	 if (self->position.y>WINDOW_HEIGHT + self->sprite->frameH) //car has gone too far down 
	 {
		 self->position.y = 0;
	 }
	 ////END: Wrap the car around the screen for the time being///
	 SDL_PollEvent( &self->carEvent ); 
		if(&self->carEvent)
					{
				
					//User presses a key
					if( self->carEvent.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( self->carEvent.key.keysym.sym )
						{
						
							case SDLK_RETURN :
						{
						slog("return is down");	
						self->carEvent.type = SDLK_CLEAR;
						break;
						}

						case SDLK_LEFT:
						self->sprite->angle -=4;
					//	slog("left is down %f", self->sprite->angle);	
						break;

						case SDLK_RIGHT:
						self->sprite->angle +=4;
					//	slog("right is down %f", self->sprite->angle);
						break;

						case SDLK_UP:

							self->acceleration.x+= dirVect.x/128;
							self->acceleration.y+= dirVect.y/128;
							
					//	slog("up is down %f", self->sprite->angle);

						break;
						
						case SDLK_DOWN:
					//	slog("down is down");
						
						self->acceleration.x = 0;
						self->acceleration.y = 0;

						/*if(self->acceleration.y == 0)
						{
						self->acceleration.y = 0;
						}*/
						break;
						}
					}

					else if( self->carEvent.type == SDL_KEYUP )
					{
						
						switch( self->carEvent.key.keysym.sym )
						{	
						
						case SDLK_RETURN :
						{
					//	slog("return is up");	
						self->carEvent.type = SDLK_CLEAR;
						break;
						}
						
						
						case SDLK_LEFT:
					//	slog("left is up");	
						self->carEvent.type = SDLK_CLEAR;
						break;

						case SDLK_RIGHT:
					//	slog("right is up");
						self->carEvent.type = SDLK_CLEAR;
						break;

						case SDLK_UP:
					//	slog("up is up");
						self->carEvent.type = SDLK_CLEAR;
						break;

						case SDLK_DOWN:
					//	slog("down is up");
						self->carEvent.type = SDLK_CLEAR;
						break;

						}
					}
		}
}
void touchCar (struct Entity_S *self, struct Entity_S *other)
{

}

void updateCar(struct Entity_S *self)
{

}

void freeCar(struct Entity_S *self)
{

}

float GetXOrign(struct Car_M *self)
{
	
	return  self->car->position.x;

}