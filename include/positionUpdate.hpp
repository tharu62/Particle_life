#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern int PARTICLE_COUNT;
float dt = 0.01f; // Assuming a fixed time step for simplicity

void updatePosition(sf::CircleShape* particles, sf::Vector2f* acceleration, sf::Vector2f* velocity){


    for(int i=0; i<PARTICLE_COUNT; ++i){
        velocity[i] += acceleration[i] * dt;
        velocity[i] *= 0.98f; // Damping factor to reduce velocity over time 
        particles[i].setPosition(particles[i].getPosition() + velocity[i] * dt);
    }

}