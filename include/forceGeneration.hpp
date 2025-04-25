#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <cmath>

#define STRENGHT 0.1f

extern int PARTICLE_COUNT;


void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration){

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i].x = 0;
        acceleration[i].y = 0;

        for(int j=0; j<PARTICLE_COUNT && j != i; ++j){
            float dx = particles[j].getPosition().x - particles[i].getPosition().x;
            float dy = particles[j].getPosition().y - particles[i].getPosition().y;
            float distance = sqrt(dx*dx + dy*dy);
            if(distance < 20 && distance > 2){

                acceleration[i].x -= dx * STRENGHT;
                acceleration[i].y -= dy * STRENGHT;
            
            }else{

                if(distance < 100 && distance > 30){
                    acceleration[i].x += dx * STRENGHT; 
                    acceleration[i].y += dy * STRENGHT;
                }
            }
        }
    }
}