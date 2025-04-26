#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <cmath>

extern float STRENGHT;
extern int PARTICLE_COUNT;


void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration){

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i].x = 0;
        acceleration[i].y = 0;

        for(int j=0; j<PARTICLE_COUNT && j != i; ++j){
            sf::Vector2f direction = particles[j].getPosition() - particles[i].getPosition();
            float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            float minimumDistance = particles[i].getRadius() * 5.f;
            float maximumDistance = particles[i].getRadius() * 20.f;

            if(distance < minimumDistance){
                acceleration[i] -= (minimumDistance - distance) * (direction/distance) * 10.f;
            }
            else if(distance <= maximumDistance && distance >= minimumDistance){
                acceleration[i] += (distance - minimumDistance) * (direction/distance);
            }
        }

        acceleration[i] *= STRENGHT;
    }
}