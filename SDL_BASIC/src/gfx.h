/*
	* Author: Jonas S.
	* Date: 02/04/2021
	! SDL2 basic Graphix Header
*/

#ifndef _GFX_H_
#define _GFX_H_

#include <SDL2/SDL.h>

#define MAKE_COLOR(r,g,b) ((uint32_t)b|((uint32_t)g<<8)|((uint32_t)r<<16))

#define COLOR_GET_B(color) (color & 0xff)
#define COLOR_GET_G(color) ((color >> 8) & 0xff)
#define COLOR_GET_R(color) ((color >> 16) & 0xff)

#define COLOR_BLACK  0x00000000
#define COLOR_RED    0x00FF0000
#define COLOR_GREEN  0x0000FF00
#define COLOR_BLUE   0x000000FF
#define COLOR_WHITE  0x00FFFFFF
#define COLOR_YELLOW 0x00FFFF00

void GFX_ClearScreen(SDL_Renderer* ren, uint32_t color);
void GFX_DrawPixel(SDL_Renderer* ren, int x, int y, uint32_t color, int alpha);
void GFX_DrawVLine(SDL_Renderer* ren, int x, int y, int s, uint32_t color, int alpha);
void GFX_DrawHLine(SDL_Renderer* ren, int x, int y, int s, uint32_t color, int alpha);
void GFX_DrawLine(SDL_Renderer* ren, int x, int y, int x2, int y2, uint32_t color, int alpha);
void GFX_DrawRect(SDL_Renderer* ren, int x, int y, int w, int h, uint32_t color, int alpha);
void GFX_DrawFillRect(SDL_Renderer* ren, int x, int y, int w, int h, uint32_t color, int alpha);
void GFX_DrawCircle(SDL_Renderer *ren, int x_, int y_, int r_, uint32_t color, int alpha);
void GFX_DrawFillCircle(SDL_Renderer *ren, int x_, int y_, int r_, uint32_t color, int alpha);

#endif