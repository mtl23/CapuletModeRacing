#ifndef __CAR_H__
#define __CAR_H__

#include "vector.h"
#include "glib.h"
#include "sprite.h"
#include "entity.h"
typedef struct Car_M

{
	int type;
	Entity_S *car;
	float angle;
	float brakes;
	float floaty;
	float health;
	float heading;
	Vector3D color_mod;

	int testBoxSize;
	int boxSize;
	int boxMass;
	SDL_Rect* chipmunkBox;
	cpFloat radius;
	cpBody *boxBody;
	cpShape *boxShape;
	cpVect startPos;


	void(*draw) (struct Entity_S *car_self, SDL_Renderer *renderer); /**logic*<*/
	void(*think) (struct Entity_S *car_self); /**logic*<*/
	void(*update) (struct Car_M *car_self); /**physics*<*/
	void(*touch) (struct Car_M *car_self, struct Entity_S *other); /**collsions*<*/
	void(*free) (struct Entity_S *car_self); /**cleanup function call on free*<*/

}Car_M;
/**
*
*@brief creates the players Car object
*/
Car_M newPlayerCar(GString *model, int type, float PosX, float PosY, float sizeX, float sizeY, cpSpace* g_space);// creates a player car entity with the path to the sprite needed.
/**
*
*@brief creates an AI Car object
*/
Car_M newCar(GString *model, int type, float PosX, float PosY, float sizeX, float sizeY);// creates a car entity with the path to the sprite needed.
// creates a car entity with the path to the sprite needed
/**
*
*@brief Sets the position Car object
*/

void SetCarPositon(Car_M car,Vector2D position);

/**
*
*@brief Draws the players Car object
*/
void drawPlayerCar(struct Entity_S *car_self, SDL_Renderer *renderer);
/**
*
*@brief Draws the AI Car objects
*/
void drawCar(struct Entity_S *car_self, SDL_Renderer *renderer);
/**
*
*@brief Car logic
*/
void thinkCar(struct Entity_S *car_self);
/**
*
*@brief Car collisiions
*/
void touchCar(struct Car_M *car_self, struct Entity_S *other);
/**
*
*@brief Updates a Car object's members
*/
void updateCar(struct Car_M *car_self);
/**
*
*@brief Frees up a Car object
*/
void freeCar(struct Car_M *car_self);
/**
*
*@brief Creates a Car Object to be used as an Obstacle
*/
Car_M newCarObstacle(GString *model, int type, float PosX, float PosY, float sizeX, float sizeY);// creates a car entity with the path to the sprite needed.


#endif
