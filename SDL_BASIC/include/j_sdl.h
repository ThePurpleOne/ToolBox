/*
		* HEADER J_SDL
		* Author : Jonas S.
		* Date   : 15/03/2022
		! SDL BASICS USAGE
*/

#ifndef _J_SDL_H_
#define _J_SDL_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// DEFINES
#define FPS 50
#define FRAME_TIME (1000 / FPS)
#define WINDOW_NAME "SDL 2.0 BASICS"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// PROTOTYPES
int32_t SDL_SpawnAll(SDL_Window **pp_win_, SDL_Renderer **pp_ren);
void SDL_killAll(SDL_Window **pp_win_, SDL_Renderer **pp_ren);

#endif