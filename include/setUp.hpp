#pragma once 

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <random>

#include "colorMatrix.hpp"

extern int PARTICLE_COUNT;

void SetParticle(sf::CircleShape* particle, int radius){

    std::random_device rd;
    std::mt19937 eng(rd());
    std::normal_distribution<double> distribution1{640.0, 640.0};
    std::normal_distribution<double> distribution2(360.0, 360.0);

    for(int i=0; i<PARTICLE_COUNT; ++i){

        float rand_1 = distribution1(eng);
        float rand_2 = distribution2(eng);

        particle[i].setRadius(radius);
        // particle[i].setFillColor(sf::Color::Red);
        particle[i].setFillColor(intToColor(rand()%2));
        particle[i].setPosition({rand_1, rand_2});
        particle[i].setOrigin( {(float) radius,(float) radius});
    
    }

}