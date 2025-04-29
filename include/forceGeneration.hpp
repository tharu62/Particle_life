#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <cmath>

#include "colorMatrix.hpp"
#include "gridSort.hpp"

extern float colorMatrix[9][9];
extern float STRENGHT;
extern int PARTICLE_COUNT;
extern int PARTICLE_RADIUS;

float minimumDistance = PARTICLE_RADIUS * 5.f;
float maximumDistance = PARTICLE_RADIUS * 20.f;

void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration, float colorMatrix[][9]){

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i] = {0,0};

        // float minimumDistance = particles[i].getRadius() * 5.f;
        // float maximumDistance = particles[i].getRadius() * 20.f;

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

void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration, float colorMatrix[][9], std::vector<Node> &grid){

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i] = {0,0};

        for(int j=0; j<grid.size(); ++j){

            if(particles[i].getPosition().x < (grid[j].center.x + maximumDistance/2) && particles[i].getPosition().x > (grid[j].center.x - maximumDistance/2) && particles[i].getPosition().y < (grid[j].center.y + maximumDistance/2) && particles[i].getPosition().y > (grid[j].center.y - maximumDistance/2)){
                
                for(int k=0; k<grid[j].particles.size() && k!=i; ++k){

                    sf::Vector2f direction = particles[k].getPosition() - particles[i].getPosition();
                    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                    
                    if(distance < minimumDistance){
                        // acceleration[i] -= (minimumDistance - distance) * (direction/distance) * 20.f;
                        acceleration[i] -= (minimumDistance - distance) * (direction/distance) * 20.f * colorMatrix[colorToInt(particles[i].getFillColor())][colorToInt(particles[k].getFillColor())];
                        // acceleration[i] -= (1/(distance/minimumDistance)) * (direction/distance);
                    }
                    else if(distance <= maximumDistance && distance >= minimumDistance){
                        acceleration[i] += (distance - minimumDistance) * (direction/distance) * colorMatrix[colorToInt(particles[i].getFillColor())][colorToInt(particles[k].getFillColor())];
                        // acceleration[i] += (distance - minimumDistance) * (direction/distance);
                    }

                }
                continue;
            }
        }

        acceleration[i] *= STRENGHT;
    }

}