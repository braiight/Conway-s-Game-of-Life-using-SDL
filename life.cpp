#include "life.hpp"


std::vector<std::vector<char> > createGrid(char *file)
{
    std::vector<std::vector<char> > grid;
    std::ifstream inputFile(file);

    std::string line;

    while (std::getline(inputFile, line))
    {
        std::vector<char> current;
        for (size_t i = 0; i < line.length(); i++)
            current.push_back(line[i]);
        grid.push_back(current);
    }
    inputFile.close();
    return (grid);
}

std::vector<std::vector<char> > getEmptyGrid()
{
    std::vector<std::vector<char> > grid;

    for (int i = 0; i < NUM_COLS; i++)
    {
        std::vector<char> current;
        for (int j = 0; j < NUM_ROWS; j++)
        {
            current.push_back('\0');
        }
        grid.push_back(current);
    }
    return (grid);
}

bool    isAlive(int x, int y, std::vector<std::vector<char> > &grid)
{
    if (grid[y][x])
        return (true);
    return (false);

}

int numNeighbors(int x, int y, std::vector<std::vector<char> >map)
{
    int y_limit = map.size() - 1;
    int x_limit = (*map.begin()).size() - 1;

    int res = 0;

    //check three neighbors above
    if (y > 0)
    {
        if (x > 0)
        {
            if (isAlive(x - 1, y - 1, map))
                res++;
        }
        if (isAlive(x, y - 1, map))
            res++;
        if (x < x_limit)
        {
            if (isAlive(x + 1, y - 1, map))
                res++;
        }
    }
    //check to the left and right
    if (x > 0)
    {
        if (isAlive(x - 1, y, map))
            res++;
    }
    if (x < x_limit)
    {
        if (isAlive(x + 1, y, map))
            res++;
    }
    //check neighbors below
    if (y < y_limit)
    {
        if (x > 0)
        {
            if (isAlive(x - 1, y + 1, map))
                res++;
        }
        if (isAlive(x, y + 1, map))
            res++;
        if (x < x_limit)
        {
            if (isAlive(x + 1, y + 1, map))
                res++;
        }
    }
    return (res);
}


void updateGrid(std::vector<std::vector<char> > &map)
{
    int y_limit = map.size();
    int x_limit = (*map.begin()).size();

    int x = 0;
    int y = 0;

    std::vector<std::vector<char> > copy(map);
    while (y < y_limit)
    {
        x = 0;
        while (x < x_limit)
        {
            if (isAlive(x, y, map) && (numNeighbors(x, y, map) < 2 || numNeighbors(x, y, map) > 3))
            {
                copy[y][x] = '\0';
            }
            if (!isAlive(x,y, map) && numNeighbors(x, y, map) == 3)
            {
                copy[y][x] = 1;
            }
            if ((isAlive(x, y, map) && !(numNeighbors(x, y, map) < 2 || numNeighbors(x, y, map) > 3)))
            {
                if (copy[y][x] != 127)
                    copy[y][x] += 1;
            }
            x++;
        }
        y++;
    }
    map = copy;
    return;
} 

void    drawGrid(SDL_Surface* surface, Grid &grid)
{
    if (grid.empty() || grid[0].empty())
        return;

    int rows = grid.size();
    int cols = grid[0].size();
    
    int cellWidth = surface->w / cols;
    int cellHeight = surface->h / rows;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            SDL_Rect cellRect;
            cellRect.x = col * cellWidth;
            cellRect.y = row * cellHeight;
            cellRect.w = cellWidth;
            cellRect.h = cellHeight;

            Uint32 color;

            int redGradient = 255;
            if (grid[row][col] != 1)
                redGradient -= (grid[row][col] * 2);
            if (isAlive(col, row, grid))
                color = SDL_MapRGB(surface->format, 255, redGradient, redGradient);
            else
                color = SDL_MapRGB(surface->format, 0, 0, 0);

            SDL_FillRect(surface, &cellRect, color);
        }
    }
}