#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <map>

//#include <ChatClient_Incomplete.hpp>
//#include <MultithreadingDemo.hpp>
#include <RaytracingExample.hpp>

using namespace std;

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode({ 1280, 720 }), "My window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if (!ImGui::SFML::Init(window))
        return -1;

    //MultithreadingDemo demo;
    RaytracingDemo demo;

    // ChatClient client;
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        float deltaTime = deltaClock.getElapsedTime().asSeconds();

        // Event Polling
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                // client.leave();
                window.close();
            }
        }

        demo.update();

        // Update
        ImGui::SFML::Update(window, deltaClock.restart());
        
        // client.render_gui();
        demo.renderImGui();

        // Render
        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

	return 0;
}