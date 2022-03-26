/*
	* CODE MAIN
	* Author : Jonas S.
	* Date   : 19/03/2022
	! BASIC TEMPLATE OPENGL
	! docs : https://docs.gl/
*/

//#include <GL/gl.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>


#define WINDOW_NAME	  "Testing OPENGL"
#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500

#define FPS		   200
#define FRAME_TIME (1000 / FPS)

int32_t SDL_GL_SpawnAll(SDL_Window** pp_win_);
void	SDL_killAll(SDL_Window** pp_win_);


// !-------------------------------
// ! ----------- SHADER -----------
// !-------------------------------

static GLfloat positions[] = { -0.8f, 0.8f, 0.8f, 0.8f,	 -0.8f, -0.8f,
							   0.8f,  0.8f, 0.8f, -0.8f, -0.8f, -0.8f };

/**
 * @brief Read the shaders from files and return an array of strings
 * 		  containing the shaders
 *
 * @param fpath_vertex
 * @param fpath_fragment
 * @return char** array[0] = vertex shader,
 * 				  array[1] = fragment shader
 */
char** read_shaders(char* fpath_vertex, char* fpath_fragment)
{
	char line[100] = { 0 };

	// ! READING VERTEX SHADER
	char  buff_vertex[1000] = { 0 };
	FILE* fp_vertex			= fopen(fpath_vertex, "r");
	if (fp_vertex == NULL)
	{
		fprintf(stderr, "Failed to open file %s\n", fpath_vertex);
		return NULL;
	}
	while (!feof(fp_vertex))
	{
		fgets(line, 100, fp_vertex);
		strcat(buff_vertex, line);
	}

	// ! READING FRAGMENT SHADER
	char  buff_fragment[1000] = { 0 };
	FILE* fp_fragment		  = fopen(fpath_fragment, "r");
	if (fp_fragment == NULL)
	{
		fprintf(stderr, "Failed to open file %s\n", fpath_fragment);
		return NULL;
	}
	while (!feof(fp_fragment))
	{
		fgets(line, 100, fp_fragment);
		strcat(buff_fragment, line);
	}

	fclose(fp_vertex);
	fclose(fp_fragment);

	char** output_array	   = malloc(sizeof(char*) * 2);
	char*  output_vertex   = strdup(buff_vertex);
	char*  output_fragment = strdup(buff_fragment);

	output_array[0] = output_vertex;
	output_array[1] = output_fragment;

	return output_array;
}


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
								 const char* fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs		 = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs		 = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

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
	SDL_Window* window = NULL;
	SDL_Event	event;

	// ! LOOP AND EVENTS VARIABLES
	bool	 running_loop = true;
	uint32_t first_ticks, ms_loop;
	float	 fps = 0;

	if (SDL_GL_SpawnAll(&window) == 0)
	{
		printf("SDL STUFF SUCCESSFULLY SPAWNED!\n");
	}

	SDL_GLContext gl_ctx = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		printf("glewInit failed: %s", glewGetErrorString(err));
		exit(1);
	}

	// ! SHADERS MANAGEMENT
	char** shaders = read_shaders("src/shaders/base_vertex.glsl",
								  "src/shaders/base_fragment.glsl");

	unsigned int shader_program = CreateShader(shaders[0], shaders[1]);

	unsigned int tr_buff;
	glGenBuffers(1, &tr_buff);
	glBindBuffer(GL_ARRAY_BUFFER, tr_buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, positions,
				 GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);

	glUseProgram(shader_program);


	glClearColor(0.1f, 0.1f, 0.1f, 0.8f);

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
		// glClearColor(1.0f, 0.4f, 0.2f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 6);
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

	// FREE AND DELETE SHADERS
	glDeleteProgram(shader_program);
	free(shaders[0]);
	free(shaders[1]);
	free(shaders);

	SDL_GL_DeleteContext(gl_ctx);
	SDL_killAll(&window);


	return 0;
}

/**
 * @brief Setup the basic SDL stuff
 *
 * @param pp_win_ Pointer to Window Pointer
 * @param pp_ren Pointer to Renderer Pointer
 * @return int32_t
 */
int32_t SDL_GL_SpawnAll(SDL_Window** pp_win_)
{
	// ! INIT SDL
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to Initialize SDL: %s", SDL_GetError());
		SDL_killAll(pp_win_);
		return EXIT_FAILURE;
	}

	// ! INIT WINDOW
	*pp_win_ = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
								WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (*pp_win_ == NULL)
	{
		printf("Unable to Initialize the Window: %s", SDL_GetError());
		SDL_killAll(pp_win_);
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
void SDL_killAll(SDL_Window** pp_win_)
{
	// Free the SDL window
	if (pp_win_)
	{
		SDL_DestroyWindow(*pp_win_);
		*pp_win_ = NULL;
	}
	printf("SDL STUFF DESTROYED AND FREED! \n");
}