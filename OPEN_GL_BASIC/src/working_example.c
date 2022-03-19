#include <SDL2/SDL.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>

static const GLuint	 WIDTH	= 512;
static const GLuint	 HEIGHT = 512;
static const GLchar* vertex_shader_source
  = "#version 120\n"
	"attribute vec2 coord2d;\n"
	"void main() {\n"
	"    gl_Position = vec4(coord2d, 0.0, 1.0);\n"
	"}\n";
static const GLchar* fragment_shader_source
  = "#version 120\n"
	"void main() {\n"
	"    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";
static GLfloat vertices[] = {
	0.0, 0.8, -0.8, -0.8, 0.8, -0.8,
};

GLuint common_get_shader_program(const char* vertex_shader_source,
								 const char* fragment_shader_source)
{
	GLchar* log = NULL;
	GLint	log_length, success;
	GLuint	fragment_shader, program, vertex_shader;

	/* Vertex shader */
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
	log = malloc(log_length);
	if (log_length > 0)
	{
		glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
		printf("vertex shader log:\n\n%s\n", log);
	}
	if (!success)
	{
		printf("vertex shader compile error\n");
		exit(EXIT_FAILURE);
	}

	/* Fragment shader */
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 0)
	{
		log = realloc(log, log_length);
		glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
		printf("fragment shader log:\n\n%s\n", log);
	}
	if (!success)
	{
		printf("fragment shader compile error\n");
		exit(EXIT_FAILURE);
	}

	/* Link shaders */
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 0)
	{
		log = realloc(log, log_length);
		glGetProgramInfoLog(program, log_length, NULL, log);
		printf("shader link log:\n\n%s\n", log);
	}
	if (!success)
	{
		printf("shader link error");
		exit(EXIT_FAILURE);
	}

	/* Cleanup. */
	free(log);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return program;
}

int main(void)
{
	GLint		  attribute_coord2d;
	GLuint		  program, vbo;
	SDL_Event	  event;
	SDL_GLContext gl_context;
	SDL_Window*	  window;

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	gl_context = SDL_GL_CreateContext(window);
	glewInit();

	/* Shader setup. */
	program
	  = common_get_shader_program(vertex_shader_source, fragment_shader_source);
	attribute_coord2d = glGetAttribLocation(program, "coord2d");

	/* Buffer setup. */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Global draw state */
	glUseProgram(program);
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Main loop. */
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glEnableVertexAttribArray(attribute_coord2d);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(attribute_coord2d);
		SDL_GL_SwapWindow(window);
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}

	/* Cleanup. */
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(program);
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}