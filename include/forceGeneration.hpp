#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <cmath>

#include "colorMatrix.hpp"

extern float colorMatrix[9][9];
extern float STRENGHT;
extern int PARTICLE_COUNT;
extern int PARTICLE_RADIUS;

void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration, float colorMatrix[][9]){

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i].x = 0;
        acceleration[i].y = 0;

        float minimumDistance = particles[i].getRadius() * 5.f;
        float maximumDistance = particles[i].getRadius() * 20.f;

        for(int j=0; j<PARTICLE_COUNT && j != i; ++j){

            sf::Vector2f direction = particles[j].getPosition() - particles[i].getPosition();
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            
            if(distance < minimumDistance){
                // acceleration[i] -= (minimumDistance - distance) * (direction/distance) * 20.f;
                acceleration[i] -= (minimumDistance - distance) * (direction/distance) * 20.f * colorMatrix[colorToInt(particles[i].getFillColor())][colorToInt(particles[j].getFillColor())];
                // acceleration[i] -= (1/(distance/minimumDistance)) * (direction/distance);
            }
            else if(distance <= maximumDistance && distance >= minimumDistance){
                acceleration[i] += (distance - minimumDistance) * (direction/distance) * colorMatrix[colorToInt(particles[i].getFillColor())][colorToInt(particles[j].getFillColor())];
                // acceleration[i] += (distance - minimumDistance) * (direction/distance);
            }
        }

        acceleration[i] *= STRENGHT;
    }
}