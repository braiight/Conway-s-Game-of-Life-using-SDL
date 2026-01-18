#ifndef LIFE_HPP
# define LIFE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <vector>

# define NUM_COLS 100
# define NUM_ROWS 100

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

using Grid = std::vector<std::vector<int> >;

void    drawGrid(SDL_Surface* surface, Grid &grid);
Grid    createGrid(char *file);
void    updateGrid(Grid &map);
Grid    getEmptyGrid();

#endif