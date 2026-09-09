#include <iostream>
#include <SFML/Graphics.hpp>

unsigned int CELL_SIZE = 5;

unsigned CELLMAP_WIDTH = 200;
unsigned CELLMAP_HEIGHT = 200;

unsigned int SCREEN_WIDTH = CELLMAP_WIDTH * CELL_SIZE;
unsigned int SCREEN_HEIGHT = CELLMAP_HEIGHT * CELL_SIZE;

void createRPentomino(std::vector<std::vector<int>>& grid, int x, int y)
{
    grid[x][y] = 1;
    grid[x+1][y] = 1;
    grid[x][y-1] = 1;
    grid[x][y-2] = 1;
    grid[x-1][y-1] = 1;

}

void createAcorn(std::vector<std::vector<int>>& grid, int x, int y)
{
    grid[x][y] = 1;
    grid[x][y-2] = 1;
    grid[x-1][y-2] = 1;
    grid[x+2][y-1] = 1;
    grid[x+3][y-2] = 1;
    grid[x+4][y-2] = 1;
    grid[x+5][y-2] = 1;
}

void createDiehard(std::vector<std::vector<int>>& grid, int x, int y)
{
    grid[x][y] = 1;
    grid[x][y-2] = 1;
    grid[x+1][y-2] = 1;
    grid[x-1][y-2] = 1;
    grid[x-5][y-2] = 1;
    grid[x-5][y-1] = 1;
    grid[x-6][y-1] = 1;
}


int main(int argc, char** argv) {
    sf::RenderWindow window;
    window.create(sf::VideoMode({ SCREEN_WIDTH,SCREEN_HEIGHT }), "Conway's Game of Life");
    window.setFramerateLimit(60);


    std::vector<std::vector<int> > grid(CELLMAP_WIDTH, std::vector<int>(CELLMAP_HEIGHT, 0));

    createDiehard(grid, 120, 110);
    createDiehard(grid, 180,180);
    createAcorn(grid, 160,160);
    createRPentomino(grid, 140, 140);
    createDiehard(grid, 20, 20);
    createDiehard(grid, 80,80);
    createAcorn(grid, 60,60);
    createRPentomino(grid, 40, 40);



    std::vector<std::vector<int> > nextGrid(CELLMAP_WIDTH, std::vector<int>(CELLMAP_HEIGHT, 0));

    while (window.isOpen())
    {

        window.clear(sf::Color::Green);
        for (int y = 0; y < CELLMAP_HEIGHT; y++)
        {


            for (int x = 0; x < CELLMAP_WIDTH; x++)
            {
                nextGrid[y][x] = 0;
                int AmountOfNeighbours = 0;

                if (y + 1 < CELLMAP_HEIGHT && grid[y + 1][x] == 1)AmountOfNeighbours++;

                if (y > 0 && grid[y - 1][x] == 1)AmountOfNeighbours++;

                if (x + 1 < CELLMAP_WIDTH && grid[y][x + 1] == 1)AmountOfNeighbours++;

                if (x > 0 && grid[y][x - 1] == 1)AmountOfNeighbours++;

                if (y + 1 < CELLMAP_HEIGHT && x + 1 < CELLMAP_WIDTH && grid[y + 1][x +1] == 1)AmountOfNeighbours++;

                if (y + 1 < CELLMAP_HEIGHT && x > 0 && grid[y + 1][x - 1] == 1)AmountOfNeighbours++;

                if (y > 0 && x + 1 < CELLMAP_WIDTH && grid[y - 1][x + 1] == 1)AmountOfNeighbours++;

                if (y > 0 && x > 0 && grid[y - 1][x - 1] == 1)AmountOfNeighbours++;

                if (grid[y][x] == 1)
                {
                    if (AmountOfNeighbours == 2 || AmountOfNeighbours == 3)
                    {
                        nextGrid[y][x] = 1;
                    }
                }
                else
                {
                    if (AmountOfNeighbours == 3)
                    {
                        nextGrid[y][x] = 1;
                    }
                }

                //if (grid[y][x] == 1 && (AmountOfNeighbours == 2|| AmountOfNeighbours == 3)) grid[y][x] = 1;



                if (nextGrid[y][x] == 1)
                {
                    sf::RectangleShape cell;
                    cell.setFillColor(sf::Color{255,70,162});
                    cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE ));

                    window.draw(cell);
                }
            }
        }
        grid = nextGrid;

        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Render
        window.display();
    }

    return 0;
}