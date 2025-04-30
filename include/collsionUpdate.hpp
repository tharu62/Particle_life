#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <math.h>

extern int PARTICLE_COUNT;

void CollisionUpdate(sf::CircleShape* particles, sf::Vector2f* velocity)
{
    for(int i=0; i<PARTICLE_COUNT; ++i){
        for(int j=0; j<PARTICLE_COUNT && j != i; ++j){
            float dx = particles[j].getPosition().x - particles[i].getPosition().x;
            float dy = particles[j].getPosition().y - particles[i].getPosition().y;
            float distance = sqrt(dx*dx + dy*dy);
            if(distance < 4){
                particles[i].setPosition({particles[i].getPosition().x - 0.1f * 2.f, particles[i].getPosition().y - 0.1f * 2.f});
                velocity[i] = {0.f, 0.f};
            }
        }
    }

}

void CollisionUpdate(sf::CircleShape* particles, std::vector<Node> &grid, float maximumDistance)
{
    int l; 
    int j;
    for(int i=0; i<PARTICLE_COUNT; ++i){

        j = findNodeFromGrid(grid, particles[i].getPosition(), 100*PARTICLE_RADIUS);
        if(j != -1){
            for(int k=0; k<grid[j].particles.size() && grid[j].particles[k]!=i; ++k){
                float dx = particles[grid[j].particles[k]].getPosition().x - particles[i].getPosition().x;
                float dy = particles[grid[j].particles[k]].getPosition().y - particles[i].getPosition().y;
                float distance = sqrt(dx*dx + dy*dy);
                if(distance < PARTICLE_RADIUS*2){
                    particles[i].setPosition({particles[i].getPosition().x - (PARTICLE_RADIUS*2 - dx), particles[i].getPosition().y - (PARTICLE_RADIUS*2 - dy)});
                }
            }
        }
    
        for(int m=0; m<8; ++m){
            if(m==0)     {l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{maximumDistance, 0.f},               100*PARTICLE_RADIUS);}
            else if(m==1){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{0.f, maximumDistance},               100*PARTICLE_RADIUS);}
            else if(m==2){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{maximumDistance, maximumDistance},   100*PARTICLE_RADIUS);}
            else if(m==3){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{-maximumDistance, 0.f},              100*PARTICLE_RADIUS);}
            else if(m==4){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{0.f, -maximumDistance},              100*PARTICLE_RADIUS);}
            else if(m==5){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{-maximumDistance, -maximumDistance}, 100*PARTICLE_RADIUS);}
            else if(m==6){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{maximumDistance, -maximumDistance},  100*PARTICLE_RADIUS);}
            else if(m==7){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{-maximumDistance, maximumDistance},  100*PARTICLE_RADIUS);}
            
            if(l != -1 && l != j){
                for(int k=0; k<grid[l].particles.size() && grid[l].particles[k]!=i; ++k){
                    float dx = particles[grid[l].particles[k]].getPosition().x - particles[i].getPosition().x;
                    float dy = particles[grid[l].particles[k]].getPosition().y - particles[i].getPosition().y;
                    float distance = sqrt(dx*dx + dy*dy);
                    if(distance < PARTICLE_RADIUS*2){
                        particles[i].setPosition({particles[i].getPosition().x - (PARTICLE_RADIUS*2 - dx), particles[i].getPosition().y - (PARTICLE_RADIUS*2- dy)});
                    }
                }
            }
        }
    }

}