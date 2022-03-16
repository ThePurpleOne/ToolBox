/*
	* Author: Jonas S.
	* Date: 02/04/2021
	! Basic test of SDL 2.0 graphics library in C
*/
// ! DOCS USED https://wiki.libsdl.org/APIByCategory

#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/gfx.h"
#include "../include/j_sdl.h"

int main()
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;

	// ! LOOP AND EVENTS VARIABLES
	bool running_loop = true;
	uint32_t first_ticks, ms_loop;
	float fps = 0;

	if (SDL_SpawnAll(&window, &renderer) == 0)
	{
		printf("SDL STUFF SUCCESSFULLY SPAWNED!\n");
	}

	while (running_loop)
	{
		first_ticks = SDL_GetTicks();

		// !-------------------------------
		// ! ------------ EVENT -----------
		// !-------------------------------
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE: // QUIT ON ESCAP
					running_loop = false;
					break;
				}
			}
		}

		// !-------------------------------
		// ! ----------- UPDATE -----------
		// !-------------------------------

		// !-------------------------------
		// ! ------------ DRAW ------------
		// !-------------------------------
		GFX_ClearScreen(renderer, COLOR_BLACK);
		GFX_DrawPixel(renderer, 10, 10, COLOR_GREEN, 255);

		// ? LINES
		GFX_DrawHLine(renderer, 20, 20, 200, COLOR_RED, 255);
		GFX_DrawVLine(renderer, 20, 20, 200, COLOR_BLUE, 255);
		GFX_DrawLine(renderer, 20, 20, 120, 400, COLOR_BLUE, 255);

		// ? SHAPES
		GFX_DrawRect(renderer, 120, 100, 700, 300, COLOR_BLACK, 255);
		GFX_DrawFillRect(renderer, 220, 150, 500, 200, COLOR_GREEN, 255);
		GFX_DrawCircle(renderer, 220, 250, 50, COLOR_BLACK, 255);
		GFX_DrawFillCircle(renderer, 720, 250, 50, COLOR_RED, 100);

		SDL_RenderPresent(renderer);

		// !-------------------------------
		// ! ------------- FPS ------------
		// !-------------------------------
		ms_loop = SDL_GetTicks() - first_ticks;
		ms_loop = ms_loop == 0 ? 1 : ms_loop; // Cap at 1 to avoir division by 0

		// if Time taken to render smaller than needed frame time
		if (ms_loop < FRAME_TIME)
		{
			SDL_Delay(FRAME_TIME - ms_loop);
		}
		ms_loop = SDL_GetTicks() - first_ticks;
		fps = 1000.0f / ms_loop;
		printf("%.0f FPS\r", fps);
	}

	SDL_killAll(&window, &renderer);
	SDL_Quit();
}
