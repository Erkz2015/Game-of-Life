#include <vector>
#include <random>
#include <memory>
#include <iostream>
#include <chrono>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

#include "Particles.hpp"
#include "Profiler.hpp"

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode({ 800, 800 }), "My window");
    window.setFramerateLimit(1000);
    window.setVerticalSyncEnabled(false);

    if (!ImGui::SFML::Init(window))
        return -1;

    Profiler profiler;
    ParticleSystem particleSystem(&window);

    sf::Clock clock;
    int frameCount = 0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    float totalTime = 0;
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asSeconds();
        totalTime += deltaTime;

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ImGui::SFML::Update(window, clock.restart());
        
        if (totalTime > .25f) {
            {
                PROFILE(profiler, "Particle Creation");
                particleSystem.spawnParticles(1000, { 400,200 });
            }
            totalTime -= .25f;
        }

        {
            PROFILE(profiler, "Particle Update");
            particleSystem.update(deltaTime);
        }

        window.clear();

        {
            PROFILE(profiler, "Particle Render");
            particleSystem.render();
        }

        // In Main to render the ImGui settings:
        // ImGui interface
        {
            // Show profiler
            profiler.renderImGui();
        }

        ImGui::SFML::Render(window);

        window.display();

        // Performance monitoring
        frameCount++;
        if (frameCount % 60 == 0) {
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime);
            std::cout << "60 frames in " << duration.count() << "ms, "
                << "Particles: " << particleSystem.getParticleCount() << std::endl;
            lastTime = now;
        }
    }

	return 0;
}