/*
 * CODE TEST
 * Author : Jonas S.
 * Date   : 19/03/2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET	"\033[0m"
#define RED		"\033[31m" /* Red */
#define GREEN	"\033[32m" /* Green */
#define WHITE	"\033[37m" /* White */
#define YELLOW	"\033[33m" /* Yellow */
#define BLUE	"\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN	"\033[36m" /* Cyan */

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

int main()
{
	char** shaders = read_shaders("src/shaders/base_vertex.shader",
								  "src/shaders/base_fragment.shader");

	printf("%s\n\n", shaders[0]);
	printf("%s\n\n", shaders[1]);

	free(shaders[0]);
	free(shaders[1]);
	free(shaders);
}