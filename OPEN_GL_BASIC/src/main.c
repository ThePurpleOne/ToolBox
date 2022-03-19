/*
	* CODE MAIN
	* Author : Jonas S.
	* Date   : 19/03/2022
	! BASIC TEMPLATE OPENGL
	! docs : https://docs.gl/
*/

//#include <GL/gl.h>
#include <GL/glew.h>
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


// !-------------------------------
// ! ----------- SHADER -----------
// !-------------------------------
static int CompileShader(unsigned int type, const char* source)
{
	unsigned int id	 = glCreateShader(type);
	const char*	 src = (const char*)source;
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);


	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		printf("Failed to compile %s shader!\n",
			   (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
		printf("%s\n", message);
		glDeleteShader(id);
		return 0;
	}


	return id;
}

static unsigned int CreateShader(const char* vertex_shader,
								 const char* fragement_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs		 = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs		 = CompileShader(GL_FRAGMENT_SHADER, fragement_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}


int main()
{
	SDL_Window*	  window   = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_GLContext gl_ctx   = NULL;

	SDL_Event event;

	// ! LOOP AND EVENTS VARIABLES
	bool	 running_loop = true;
	uint32_t first_ticks, ms_loop;
	float	 fps = 0;

	if (SDL_GL_SpawnAll(&window, &renderer, &gl_ctx) == 0)
	{
		printf("SDL STUFF SUCCESSFULLY SPAWNED!\n");
	}


	// !-------------------------------
	// ! ----- OPENGL WEIRD THINGS ----
	// !-------------------------------
	// If using GLEW version 1.13 or earlier
	glewExperimental = true;
	GLenum err		 = glewInit();
	if (err != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed: %s", glewGetErrorString(err));
		exit(1);
	}

	// !-------------------------------
	// ! ---------- TRIANGLE ----------
	// !-------------------------------

	// SET DATA IN THE VIDEO MEMORY BEFORE TO BE DRAWN
	float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f };

	unsigned int tr_buff;
	glGenBuffers(1, &tr_buff);
	glBindBuffer(GL_ARRAY_BUFFER, tr_buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
	printf("TRIANGLE SUCCESFULLY CREATED IN VIDEO MEMORY\n");

	// CREATE AN ACTUAL SHADER
	char* vertex_shader = "#version 330 core\n"
						  "in vec4 position;\n"
						  "void main()\n"
						  "{\n"
						  "	gl_Position = position;\n"
						  "}\n";

	char* fragment_shader = "#version 330 core\n"
							"out vec4 color;\n"
							"void main()\n"
							"{\n"
							"	color = vec4(1.0, 1.0, 1.0, 0.5);\n"
							"}\n";

	unsigned int shader_program = CreateShader(vertex_shader, fragment_shader);
	glUseProgram(shader_program);


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

		glDrawArrays(GL_TRIANGLES, 0, 3);

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
						SDL_GLContext* p_gl_ctx_)
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	// ! SET ATTRIBUTES FOR OPENGL BEFORE CREATING THE CONTEXT
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
						SDL_GL_CONTEXT_PROFILE_CORE);

	// ! CREATE THE CONTEXT
	p_gl_ctx_ = SDL_GL_CreateContext(*pp_win_);

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