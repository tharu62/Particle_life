#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern int PARTICLE_COUNT;
float dt = 0.01f; // Assuming a fixed time step for simplicity

void updatePosition(sf::CircleShape* particles, sf::Vector2f* acceleration){


    for(int i=0; i<PARTICLE_COUNT; ++i){

        particles[i].setPosition(particles[i].getPosition() + acceleration[i] * dt * dt);
    }

}