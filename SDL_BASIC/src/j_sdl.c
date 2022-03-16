/*
	* CODE J_SDL
	* Author : Jonas S.
	* Date   : 15/03/2022
	! SDL 2.0 basic test
*/
#include "../include/j_sdl.h"

/**
 * @brief Setup the basic SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @param pp_ren Pointer to Renderer Pointer
 * @return int32_t
 */
int32_t SDL_SpawnAll(SDL_Window **pp_win_, SDL_Renderer **pp_ren)
{
	// ! INIT SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to Initialize SDL: %s", SDL_GetError());
		SDL_killAll(pp_win_, pp_ren);
		return EXIT_FAILURE;
	}

	// ! INIT WINDOW
	*pp_win_ = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (*pp_win_ == NULL)
	{
		printf("Unable to Initialize the Window: %s", SDL_GetError());
		SDL_killAll(pp_win_, pp_ren);
		return EXIT_FAILURE;
	}

	// ! INIT RENDERER
	*pp_ren = SDL_CreateRenderer(*pp_win_, -1, SDL_RENDERER_ACCELERATED);
	if (*pp_ren == NULL)
	{
		printf("Unable to Initialize the Window: %s", SDL_GetError());
		SDL_killAll(pp_win_, pp_ren);
		return EXIT_FAILURE;
	}

	return 0;
}

/**
 * @brief Destroy and free the SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @param pp_ren Pointer to Renderer Pointer
 */
void SDL_killAll(SDL_Window **pp_win_, SDL_Renderer **pp_ren)
{
	// Free the SDL renderer
	if (pp_ren)
	{
		SDL_DestroyRenderer(*pp_ren);
		*pp_ren = NULL;
	}

	// Free the SDL window
	if (pp_win_)
	{
		SDL_DestroyWindow(*pp_win_);
		*pp_win_ = NULL;
	}
	printf("SDL STUFF DESTROYED AND FREED! \n");
}
