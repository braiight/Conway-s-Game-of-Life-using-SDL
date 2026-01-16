#include <iostream>
#include <SDL2/SDL.h>
#include "life.hpp"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return (1);
	} 

	window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cerr << "Error creating window: " << SDL_GetError()  << std::endl;
		return (1);
	}

	winSurface = SDL_GetWindowSurface(window);
	if (!winSurface)
	{
		std::cerr << "Error getting surface: " << SDL_GetError() << std::endl;
		return (1);
	}

	bool running = true;
	bool mousePressed = false;
    SDL_Event event;

	Grid grid; // Disabling creating a grid from a text file 
	// if (argc == 1)
		grid = getEmptyGrid();
	// else
		// grid = createGrid(argv[1]);

    int cellWidth = winSurface->w / grid[0].size();
    int cellHeight = winSurface->h / grid.size();

	//main loop
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
			if (event.type == SDL_MOUSEBUTTONDOWN)
				mousePressed = true;
			
			// Draw new cells using the mouse
			while (mousePressed)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_MOUSEBUTTONUP)
						mousePressed = false;
				}
				int mouseX;
				int mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				mouseX /= cellWidth;
				mouseY /= cellHeight;
				if (mouseY >= 0 && mouseY < (int)grid.size() &&
					mouseX >= 0 && mouseX < (int)grid[0].size())
				{
					grid[mouseY][mouseX] = 1;
				}
				drawGrid(winSurface, grid);
				SDL_UpdateWindowSurface(window);
				SDL_Delay(50);
			}
        }


        // Render
		updateGrid(grid);
        drawGrid(winSurface, grid);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(50);
    }

	// This will also destroy the surface
	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return (0);
}
