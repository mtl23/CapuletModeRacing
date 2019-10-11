#ifndef __BG_H__
#define __BG_H__
#include "sprite.h"
#include "camera.h"
/**
 * @brief Draws the background
 * @param bg1 the grass
 */
void DrawBG(Sprite_M bg1, camera_M cam);
/**
 * @brief sets original background parameters
 */
void SetBG();
#endif