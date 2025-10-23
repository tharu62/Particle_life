#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f acceleration;
};