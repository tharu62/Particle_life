#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>

extern int PARTICLE_COUNT;

void CollisionUpdate(sf::CircleShape* particles, sf::Vector2f* velocity){

    for(int i=0; i<PARTICLE_COUNT; ++i){
        for(int j=0; j<PARTICLE_COUNT && j != i; ++j){
            float dx = particles[j].getPosition().x - particles[i].getPosition().x;
            float dy = particles[j].getPosition().y - particles[i].getPosition().y;
            float distance = sqrt(dx*dx + dy*dy);
            if(distance < 2){
                particles[i].setPosition({particles[i].getPosition().x + dx * 2.f, particles[i].getPosition().y + dy * 2.f});
                velocity[i] = {0.f, 0.f};
            }
        }
    }

}