/*
 * CODE TEST
 * Author : Jonas S.
 * Date   : 19/03/2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void parse_shader(char* file_path)
{
	FILE* fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		printf("Failed to open file %s\n", file_path);
		return;
	}
	printf("DEBUG - AFTER OPENNING FILE \n");

	// ! GET TO THE BEGINNING OF SHADER VERTEX
	while (1) // ? LOOK FOR SHADER VERTEX
	{
		char* line = malloc(sizeof(char) * 100);
		getline(&line, NULL, fp);
		printf("DEBUG - GETLINE PROBLEM\n");
		printf("LINE :  %s\n", line);

		if (strstr(line, "#shader vertex") != NULL)
		{
			printf("DEBUG - STR STR  PROBLEM\n");
			break;
		}
		printf("DID NOT BREAK\n");
	} // QUIT WHEN FOUND "shader vertex"

	// printf("DEBUG - FOUND SHADER VERTEX\n");

	// char buff_shader_vertex[1000];
	// while (1) // ? READ THE SHADER UNTIL END SHADER VERTEX
	//{
	//	if (!feof(fp))
	//		return;

	//	char* line = NULL;
	//	getline(&line, NULL, fp);

	//	if (strstr(line, "#end shader vertex") != NULL)
	//		break;

	//	// Copy the shader string line by line into the buffer
	//	strcat(line, buff_shader_vertex);
	//} // QUIT WHEN FOUND "end shader vertex"

	//// ! GET TO THE BEGINNING OF FRAGMENT SHADER
	// while (1) // ? LOOK FOR FRAGMENT SHADER
	//{
	//	if (!feof(fp))
	//		return;

	//	char* line = NULL;
	//	getline(&line, NULL, fp);

	//	if (strstr(line, "#fragment vertex") != NULL)
	//		break;
	//} // QUIT WHEN FOUND "shader vertex"

	// char buff_shader_fragment[1000];
	// while (1) // ? READ THE SHADER UNTIL END SHADER FRAGMENT
	//{
	//	if (!feof(fp))
	//		return;

	//	char* line = NULL;
	//	getline(&line, NULL, fp);

	//	if (strstr(line, "#end shader vertex") != NULL)
	//		break;

	//	// Copy the shader string line by line into the buffer
	//	strcat(line, buff_shader_fragment);
	//} // QUIT WHEN FOUND "end shader fragment"

	// fclose(fp);

	// printf("%s\n", buff_shader_vertex);
	// printf("%s\n", buff_shader_fragment);
}


int main()
{
	parse_shader("src/shaders/base.shader");
	printf("TEST \n");
}