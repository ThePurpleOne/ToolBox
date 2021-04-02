/*
    * Author: Jonas S.
    * Date: 02/04/2021
    ! Basic test of SDL 2.0 graphics library in C
*/
// ! DOCS USED https://wiki.libsdl.org/APIByCategory

#include <stdio.h>
#include <SDL2/SDL.h>
#include "gfx.h"


#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 1000
#define BACKGROUND_COLOR COLOR_WHITE

int main(int argc, char *argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;

    //! FPS related
    unsigned int currentTime;
    unsigned int lastTime;



    // ! INITs
    {
        // ?Try to initialise SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            printf("Unable to Initialize SDL: %s", SDL_GetError());
            return 1;
        }
        
        window = SDL_CreateWindow("OSEF", 
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT, 0);

        renderer = SDL_CreateRenderer( window, 
                                -1, 
                                SDL_RENDERER_ACCELERATED);

        // ?Check if Window init was successful
        if (window == NULL)
        {
            printf("Unable to Initialize the Window: %s", SDL_GetError());
            return 1;
        }

        // ?Check if renderer init was successful
        if (renderer == NULL)
        {
            printf("Unable to Initialize the Window: %s", SDL_GetError());
            return 1;
        }
    }
    // ! END INITs

    while(1)
    {
        // ! Handle Quit event
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) 
            {
                printf("\n\nProgram has been terminated after %f seconds\n", (double)event.quit.timestamp / 1000 );
                break;
            }
        }
        // ! END Handle Quit event

        // TODO Make an average and add delay to get capped FPS
        // ! show fps 
            currentTime = SDL_GetTicks();  //number of ms since init
            printf("\rFPS : %f", 1000.0 / (double)(currentTime - lastTime) );
            lastTime = currentTime;
            SDL_Delay(5);
        // ! END Limit and show fps


        GFX_ClearScreen(renderer, BACKGROUND_COLOR);
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

        //Render renderer to the window
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
