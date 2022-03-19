/*
	* CODE MAIN
	* Author : Jonas S.
	* Date   : 19/03/2022
	! BASIC TEMPLATE OPENGL
*/

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_NAME	  "Testing OPENGL"
#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500

#define FPS		   200
#define FRAME_TIME (1000 / FPS)

int32_t SDL_GL_SpawnAll(SDL_Window**   pp_win_,
						SDL_Renderer** pp_ren,
						SDL_GLContext* pp_gl_ctx_);
void	SDL_killAll(SDL_Window** pp_win_, SDL_Renderer** pp_ren);

int main()
{
	SDL_Window*	  window   = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_GLContext gl_ctx_  = NULL;

	SDL_Event event;

	// ! LOOP AND EVENTS VARIABLES
	bool	 running_loop = true;
	uint32_t first_ticks, ms_loop;
	float	 fps = 0;

	if (SDL_GL_SpawnAll(&window, &renderer, &gl_ctx_) == 0)
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
		glClearColor(1.0f, 0.4f, 0.2f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);

		// !-------------------------------
		// ! ------------- FPS ------------
		// !-------------------------------
		ms_loop = SDL_GetTicks() - first_ticks;
		ms_loop = ms_loop == 0 ? 1 : ms_loop;
		// Cap at 1 to avoir division by 0
		// if Time taken to render smaller than needed frame time
		if (ms_loop < FRAME_TIME)
		{
			SDL_Delay(FRAME_TIME - ms_loop);
		}
		ms_loop = SDL_GetTicks() - first_ticks;
		fps		= 1000.0f / ms_loop;
		printf("%.0f FPS\r", fps);
	}

	SDL_killAll(&window, &renderer);

	return 0;
}

/**
 * @brief Setup the basic SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @param pp_ren Pointer to Renderer Pointer
 * @return int32_t
 */
int32_t SDL_GL_SpawnAll(SDL_Window**   pp_win_,
						SDL_Renderer** pp_ren,
						SDL_GLContext* pp_gl_ctx_)
{
	// ! INIT SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to Initialize SDL: %s", SDL_GetError());
		SDL_killAll(pp_win_, pp_ren);
		return EXIT_FAILURE;
	}

	// ! INIT WINDOW
	*pp_win_ = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
								WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (*pp_win_ == NULL)
	{
		printf("Unable to Initialize the Window: %s", SDL_GetError());
		SDL_killAll(pp_win_, pp_ren);
		return EXIT_FAILURE;
	}

	// ! SET OPENGL VERSION TO 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// ! SET ATTRIBUTES FOR OPENGL BEFORE CREATING THE CONTEXT
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);

	// ! CREATE THE CONTEXT
	pp_gl_ctx_ = SDL_GL_CreateContext(*pp_win_);

	return 0;
}

/**
 * @brief Destroy and free the SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @param pp_ren Pointer to Renderer Pointer
 */
void SDL_killAll(SDL_Window** pp_win_, SDL_Renderer** pp_ren)
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