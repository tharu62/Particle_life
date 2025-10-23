#pragma once 

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <random>

#include "colorMatrix.hpp"

extern int PARTICLE_COUNT;

/**
 * @brief Sets up the particles with random position and color in a rectangle of 1280x720 on screen.
 * 
 * @param particle Pointer to an array of CircleShape particles.
 * @param radius The radius of each particle.
 */
void SetParticle(sf::CircleShape* particle, int radius){

    std::random_device rd;
    std::mt19937 eng(rd());
    std::normal_distribution<double> distribution1{640.0, 640.0};
    std::normal_distribution<double> distribution2(360.0, 360.0);

    for(int i=0; i<PARTICLE_COUNT; ++i){

        float rand_1 = distribution1(eng);
        float rand_2 = distribution2(eng);

        particle[i].setRadius(radius);
        particle[i].setFillColor(intToColor(rand()%3));
        particle[i].setPosition({rand_1, rand_2});
        while(particle[i].getPosition().x <= 0 || particle[i].getPosition().x >= 1280){
            rand_1 = distribution1(eng);
            particle[i].setPosition({rand_1, particle[i].getPosition().y});
        }
        while(particle[i].getPosition().y <= 0 || particle[i].getPosition().y >= 720){
            rand_2 = distribution2(eng);
            particle[i].setPosition({particle[i].getPosition().x, rand_2});
        }
        particle[i].setOrigin( {(float) radius,(float) radius});
    
    }

}