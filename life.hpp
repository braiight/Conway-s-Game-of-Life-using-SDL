#ifndef LIFE_HPP
# define LIFE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <vector>

# define NUM_COLS 80
# define NUM_ROWS 80

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

using Grid = std::vector<std::vector<char> >;

void    drawGrid(SDL_Surface* surface, Grid &grid);
Grid    createGrid(char *file);
void    updateGrid(std::vector<std::vector<char> > &map);
Grid    getEmptyGrid();

#endif