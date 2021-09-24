/*
	* CODE MAIN
	* Author : Jonas S.
	* Date   : 24/09/2021
	! Basic Project Raylib
	? Source : www.raylib.com
*/

#include <stdio.h>
#include "raylib.h"

int main()
{
	const int screenWidth = 1000;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "BASIC WINDOW");
	
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing(); // ! DRAWING

		DrawFPS(10, 10); 
		ClearBackground(LIGHTGRAY);

		DrawRectangleRec((Rectangle) {100, 100, 300, 300}, LIME);
		DrawCircle(250, 250, 50, SKYBLUE);

		EndDrawing(); // ! END DRAWING
	}

	CloseWindow();

	return 0;
}