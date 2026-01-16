#ifndef LIFE_HPP
# define LIFE_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <vector>

# define NUM_COLS 70
# define NUM_ROWS 70

using Grid = std::vector<std::vector<char> >;

void    drawGrid(SDL_Surface* surface, Grid &grid);
Grid    createGrid(char *file);
void    updateGrid(std::vector<std::vector<char> > &map);
Grid    getEmptyGrid();

#endif