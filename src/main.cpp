#include <iostream>
#include <SFML/Graphics.hpp>

unsigned int CELL_SIZE = 5;

unsigned CELLMAP_WIDTH = 200;
unsigned CELLMAP_HEIGHT = 200;

unsigned int SCREEN_WIDTH = CELLMAP_WIDTH * CELL_SIZE;
unsigned int SCREEN_HEIGHT = CELLMAP_HEIGHT * CELL_SIZE;


int main(int argc, char** argv) {
    sf::RenderWindow window;
    window.create(sf::VideoMode({ SCREEN_WIDTH,SCREEN_HEIGHT }), "Conway's Game of Life");
    window.setFramerateLimit(60);


    std::vector<std::vector<int> > grid(CELLMAP_WIDTH, std::vector<int>(CELLMAP_HEIGHT, 0));
    grid[100][100] = 1;


    while (window.isOpen())
    {

        window.clear(sf::Color::Green);
        for (int y = 0; y < CELLMAP_HEIGHT; y++)
        {
            for (int x = 0; x < CELLMAP_WIDTH; x++)
            {
                if (grid[y][x] == 1)
                {
                    sf::RectangleShape cell;
                    cell.setFillColor(sf::Color{255,70,162});
                    cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE ));

                    window.draw(cell);
                }
            }
        }

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


