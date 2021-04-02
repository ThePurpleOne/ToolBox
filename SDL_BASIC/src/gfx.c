/*
	* Author: Jonas S.
	* Date: 02/04/2021
	! SDL2 basic Graphix C code 
*/

#include "gfx.h"

void GFX_ClearScreen(SDL_Renderer* ren, uint32_t color)
{
	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), 255);
	SDL_RenderClear(ren);
}

void GFX_DrawPixel(SDL_Renderer* ren, int x, int y, uint32_t color, int alpha)
{
	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
	SDL_RenderDrawPoint(ren, x, y);
}

void GFX_DrawVLine(SDL_Renderer* ren, int x, int y, int s, uint32_t color, int alpha)
{
	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
	SDL_RenderDrawLine(ren, x, y, x+s, y);
}

void GFX_DrawHLine(SDL_Renderer* ren, int x, int y, int s, uint32_t color, int alpha)
{
	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
	SDL_RenderDrawLine(ren, x, y, x, y+s);
}

void GFX_DrawLine(SDL_Renderer* ren, int x, int y, int x2, int y2, uint32_t color, int alpha)
{
	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
	SDL_RenderDrawLine(ren, x, y, x2, y2);
}


void GFX_DrawFillRect(SDL_Renderer* ren, int x, int y, int w, int h, uint32_t color, int alpha)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
	SDL_RenderFillRect(ren, &r);
}

void GFX_DrawRect(SDL_Renderer* ren, int x, int y, int w, int h, uint32_t color, int alpha)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
	SDL_RenderDrawRect(ren, &r);
}

void GFX_DrawCircle(SDL_Renderer *ren, int x_, int y_, int r_, uint32_t color, int alpha)
{
	// Don't know how to draw circle, so i took someone's fucntion
	// SOURCE https://gist.github.com/derofim/912cfc9161269336f722

	double error = (double)-r_;
	double x = (double)r_ - 0.5;
	double y = (double)0.5;
	double cx = x_ - 0.5;
	double cy = y_ - 0.5;

	while (x >= y)
	{
		GFX_DrawPixel(ren, (int)(cx + x), (int)(cy + y), color, alpha);
		GFX_DrawPixel(ren, (int)(cx + y), (int)(cy + x), color, alpha);

		if (x != 0)
		{
			GFX_DrawPixel(ren, (int)(cx - x), (int)(cy + y), color, alpha);
			GFX_DrawPixel(ren, (int)(cx + y), (int)(cy - x), color, alpha);
		}

		if (y != 0)
		{
			GFX_DrawPixel(ren, (int)(cx + x), (int)(cy - y), color, alpha);
			GFX_DrawPixel(ren, (int)(cx - y), (int)(cy + x), color, alpha);
		}

		if (x != 0 && y != 0)
		{
			GFX_DrawPixel(ren, (int)(cx - x), (int)(cy - y), color, alpha);
			GFX_DrawPixel(ren, (int)(cx - y), (int)(cy - x), color, alpha);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}

	}
}

void GFX_DrawFillCircle(SDL_Renderer *ren, int x_, int y_, int r_, uint32_t color, int alpha)
{
	// Don't know how to draw circle, so i took someone's fucntion
	// SOURCE https://gist.github.com/derofim/912cfc9161269336f722
	static const int BPP = 4;

	for (double dy = 1; dy <= r_; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * r_ * dy) - (dy * dy)));
		int x = x_ - dx;
		SDL_SetRenderDrawColor(ren, COLOR_GET_R(color), COLOR_GET_G(color), COLOR_GET_B(color), alpha);
		SDL_RenderDrawLine(ren, x_ - dx, y_ + dy - r_, x_ + dx, y_ + dy - r_);
		SDL_RenderDrawLine(ren, x_ - dx, y_ - dy + r_, x_ + dx, y_ - dy + r_);
	}
}









