#include <chipmunk.h>
#include"Physics.h"

cpSpace *InitPhysicsSystem()
{


	cpSpace *g_space = NULL;
	g_space = cpSpaceNew();
	cpVect gravity = cpv(0, -10);
	cpSpaceSetGravity(g_space, gravity);

	return g_space;
}