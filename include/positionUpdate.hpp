#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern int PARTICLE_COUNT;
extern sf::Vector2f topLeftgridCorner;
extern sf::Vector2f topRightgridCorner;
extern sf::Vector2f bottomLeftgridCorner;
extern sf::Vector2f bottomRightgridCorner;
float dt = 0.01f; // Assuming a fixed time step for simplicity

/**
 * @brief Updates the position of particles based on their velocity and acceleration.
 * 
 * @param particles Array of particles to update.
 * @param acceleration Array of accelerations for each particle.
 * @param velocity Array of velocities for each particle.
 */
void updatePosition(sf::CircleShape* particles, sf::Vector2f* acceleration, sf::Vector2f* velocity){


    for(int i=0; i<PARTICLE_COUNT; ++i){
        if(particles[i].getPosition().x < topLeftgridCorner.x || particles[i].getPosition().x > topRightgridCorner.x || particles[i].getPosition().y < topLeftgridCorner.y || particles[i].getPosition().y > bottomLeftgridCorner.y){
            velocity[i].x = 0.0f;
        }else{
            velocity[i] += acceleration[i] * dt;
            velocity[i] *= 0.98f; // Damping factor to reduce velocity over time 
            particles[i].setPosition(particles[i].getPosition() + velocity[i] * dt);
        }
    }

}