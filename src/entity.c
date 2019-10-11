#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "SDL_image.h"
#include "entity.h"
#include "vector.h"
#include "simple_logger.h"

extern SDL_Renderer* g_renderer;

Entity_S *entityList = NULL;
int numEntity = 0;
int entityMax = 10;


void InitEntitySystem(int EntityMax)
{

	if(numEntity == entityMax)
	{
	slog("Cannot init entities");
	return;
	}
		entityList = (Entity_S*)malloc(sizeof(Entity_S)*(entityMax));

	if(entityList == NULL)
	{
		slog("failed to initialize entity system. STILL NULL");
	}
memset(entityList, 0, sizeof(Entity_S)*(entityMax));
slog("Entity system is go");

atexit(CloseEntitySystem);
}



void CloseEntitySystem()

{
   if(!entityList)
   {
		return;
   }
  
slog("entity system is closed");
free(entityList);
entityList=NULL;
numEntity = 0;
}


Entity_S* EntityNew()
{
	int i; 
	char snum[5];
	char fileStr[32];
	for( i= 0 ; i < entityMax; i++ )
	{

		itoa(i, snum, 10);

		if(entityList[i].inuse)
		{
			continue;
		}
		memset(&entityList[i],0,sizeof(Entity_S));
		entityList[i].inuse = 1; 
		
		strcpy(fileStr, "Entity");
		strcat(fileStr, snum);
		strncpy(entityList[i].filename, fileStr, 20);
		
		slog("NEW ENTITY");
		if(!&entityList[i])
		{
			slog("ENTITY ALLOCATION FAILED");
			return NULL;
		}

		return &entityList[i];
	}
}



void entityFree(Entity_S **entity)
{
	(*entity)->inuse= 0;
	*entity = NULL;
  
}

void entityFree(Entity_S *entity)
{
	entity->inuse= 0;
	entity = NULL;
  
}


Entity_S *entityLoad(char *filename, Vector2D position) //should load the sprite of entity if needed
{
  int i;
   Entity_S *temp;
   temp = EntityNew();
  Sprite_M temp_spr = *spriteLoad(filename,position.x,position.y);


  /*makesure we have the room for a entity*/
  if(numEntity + 1 >= entityMax)
  {
      slog( "Maximum Entities Reached.");
        exit(1);
  }
  /*if its not already in memory, then load it.*/
  
  numEntity++;
  temp->sprite = &temp_spr;
  strncpy(temp->filename, temp_spr.filename,20);
  for(i = 0;i <= numEntity;i++)
  {
    if(entityList[i].inuse)break;
  }

  if(&temp == NULL)
  {
  slog("unable to load a vital sprite: %s",SDL_GetError());
  exit(0);
  }
 slog("loaded an entity for the first time");


 temp->inuse = 1;
  return temp;
}

void entityDraw(Entity_S *entity, SDL_Renderer* renderer, int frame, Vector2D dimentions, Vector2D position)
{
	if((!entity)||(!renderer))
	{
		
		slog("no valid entity or renderer");
		return;
	}

	if(!&entity->sprite)
	{
	
		slog("no valid entity sprite");
		return;
	}
	spriteDraw(entity->sprite, g_renderer, frame, dimentions,position);
}

void entityDraw(struct Entity_S *self, SDL_Renderer *renderer) // used for the player's car
{
	Vector2D pos;
	pos.x = self->position.x;
	pos.y = self->position.y;
	Vector2D dim;
	dim.x = self->size.x;
	dim.y = self->size.y;
	spriteDraw(self->sprite, renderer, 0, dim, pos);
}

void entityThinkAll()
{
 int i;
 for(i=0;i<entityMax;i++)
 {
	 if(!entityList[i].inuse)
	 {
		continue;
	 }
	 if(!entityList[i].think)
	 {
		continue;
	 }
	 entityList[i].think(&entityList[i]);
 }
}

void entityUpdateAll()
{
 int i;
 for(i=0;i<entityMax;i++)
 {
	 if(!entityList[i].inuse)
	 {
		continue;
	 }
	 if(!entityList[i].update)
	 {
		continue;
	 }
	 entityList[i].update(&entityList[i]);

	}

}

void entityDrawAll()
{
 int i;
 for(i=0;i<entityMax;i++)
 {
  if(!entityList[i].inuse)
	 {
		continue;
	 }
	 if(!entityList[i].draw)
	 {
		continue;
	 }
	 entityList[i].draw(&entityList[i],g_renderer);
	}

 }

void entityFreeAll()
{
	
	int i;
	for (i = 0; i<entityMax; i++)
	{	
		entityFree(&entityList[i]);
	}

}