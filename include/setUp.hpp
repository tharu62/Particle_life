#pragma once 

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <random>

#include "colorMatrix.hpp"

extern int PARTICLE_COUNT;
extern sf::Vector2f topLeftgridCorner;
extern sf::Vector2f topRightgridCorner;
extern sf::Vector2f bottomLeftgridCorner;
extern sf::Vector2f bottomRightgridCorner;

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
    std::normal_distribution<double> distribution2(640.0, 640.0);

    for(int i=0; i<PARTICLE_COUNT; ++i){

        float rand_1 = distribution1(eng);
        float rand_2 = distribution2(eng);

        particle[i].setRadius(radius);
        particle[i].setFillColor(intToColor(rand()%4));
        particle[i].setPosition({rand_1, rand_2});
        while(particle[i].getPosition().x <= topLeftgridCorner.x || particle[i].getPosition().x >= topRightgridCorner.x){
            rand_1 = distribution1(eng);
            particle[i].setPosition({rand_1, particle[i].getPosition().y});
        }
        while(particle[i].getPosition().y <= topLeftgridCorner.y || particle[i].getPosition().y >= bottomLeftgridCorner.y){
            rand_2 = distribution2(eng);
            particle[i].setPosition({particle[i].getPosition().x, rand_2});
        }
        particle[i].setOrigin( {(float) radius,(float) radius});
    
    }

}