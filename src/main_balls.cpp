#include "imgui.h"
#include "imgui-SFML.h"
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <Balls.hpp>

#include <ChatClient.hpp>

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode({ 800, 800 }), "My window");
    window.setFramerateLimit(1000);
    window.setVerticalSyncEnabled(false);

    if (!ImGui::SFML::Init(window))
        return -1;
    
    // Load font for text rendering
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        // If arial.ttf not found, try system default or any other font
        // You might need to provide a path to a font file on your system
        std::cerr << "Warning: Could not load font. Text may not display correctly.\n";
    }

    // Create text object for deltaTime display
    sf::Text deltaTimeText = sf::Text(font, "TEST");
    deltaTimeText.setFont(font);
    deltaTimeText.setCharacterSize(24);
    deltaTimeText.setFillColor(sf::Color::White);
    deltaTimeText.setPosition(sf::Vector2f(10.0f, 10.0f));

    float deltaTotal = 0.0f;
    int fps = 0;
    int fpsDisplay = 0;

    BallGame ballGame;
    sf::Vector2u windowSize = window.getSize();

    windowSize.x -= 10.0f;
    windowSize.y -= 10.0f;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update balls
        ballGame.updateBalls(windowSize, deltaTime);

        deltaTotal += deltaTime;
        fps++;

        window.clear();

        // Update deltaTime text
        deltaTimeText.setString("FPS: " + std::to_string(fpsDisplay));

        if (deltaTotal > 1.0f) {
            deltaTotal -= 1.0f;
            fpsDisplay = fps;
            fps = 0;
        }

        ballGame.drawBalls(window);
        
        window.draw(deltaTimeText); // Draw deltaTime text

        window.display();
    }

	return 0;
}