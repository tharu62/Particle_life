#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <cmath>

#include "colorMatrix.hpp"
#include "grid.hpp"

#define color_row(x) colorToInt(particles[x].getFillColor())
#define color_col(y,z) colorToInt(particles[grid[y].particles[z]].getFillColor())


extern int PARTICLE_COUNT;
extern int PARTICLE_RADIUS;
extern float STRENGHT;
extern float REPULSION_FACTOR;
extern int GRID_CELL_SIZE;

// float minimumDistance = PARTICLE_RADIUS * 3.f;
float minimumDistance = PARTICLE_RADIUS * 5.f;
float maximumDistance = PARTICLE_RADIUS * 20.f;
float minimumDistanceSquared = minimumDistance * minimumDistance;
float maximumDistanceSquared = maximumDistance * maximumDistance;

/**
 * @brief Updates the acceleration of particles based on their acceleration, position and color.
 * @param particles Array of particles.
 * @param acceleration Array of accelerations for each particle.
 * @param colorMatrix Color matrix used for color manipulation.
 */
void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration, float (&colorMatrix)[9][9])
{
    sf::Vector2f direction;
    float distance;

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i] = {0,0};

        for(int j=0; j<PARTICLE_COUNT && j != i; ++j){

            direction = particles[j].getPosition() - particles[i].getPosition();
            distance = direction.x * direction.x + direction.y * direction.y;
            
            if(distance < maximumDistanceSquared){
                
                if(distance < minimumDistanceSquared && distance > 0){
                    distance = sqrt(distance);
                    acceleration[i] -= (minimumDistance - distance) * (direction/distance) * REPULSION_FACTOR;
                }
                else if(distance <= maximumDistanceSquared && distance >= minimumDistanceSquared){
                    distance = sqrt(distance);
                    acceleration[i] += (float)abs(log(distance)) * (direction/distance) * colorMatrix[color_row(i)][color_row(j)];
                }

            }
        }

        acceleration[i] *= STRENGHT;
    }
}

/**
 * @brief Updates the acceleration of particles based on their acceleration, position, color and grid.
 * @param particles Array of particles.
 * @param acceleration Array of accelerations for each particle.
 * @param colorMatrix Color matrix used for color manipulation.
 * @param grid Grid containing nodes with particles.
 */
void updateForces(sf::CircleShape* particles, sf::Vector2f* acceleration, float colorMatrix[][9], std::vector<Node> &grid)
{
    int l; 
    int j;

    for(int i=0; i<PARTICLE_COUNT; ++i){

        acceleration[i] = {0,0};

        j = findNodeFromGrid(grid, particles[i].getPosition(), GRID_CELL_SIZE);
        if(j != -1){
            for(int k=0; k<grid[j].particles.size() && grid[j].particles[k]!=i; ++k){
    
                sf::Vector2f direction = particles[grid[j].particles[k]].getPosition() - particles[i].getPosition();
                float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                
                if(distance < minimumDistance && distance > 0){ 
                    acceleration[i] -= (minimumDistance - distance) * (direction/distance) * REPULSION_FACTOR;
                }
                else if(distance <= maximumDistance && distance >= minimumDistance){
                    acceleration[i] += (float)abs(log(distance)) * (direction/distance) * colorMatrix[color_row(i)][color_col(j,k)];
                }
    
            }
            
            for(int m=0; m<8; ++m){
                if(m==0)     {l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{(float) GRID_CELL_SIZE,                    0.f},  GRID_CELL_SIZE);}
                else if(m==1){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{                   0.f, (float) GRID_CELL_SIZE},  GRID_CELL_SIZE);}
                else if(m==2){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{(float) GRID_CELL_SIZE, (float) GRID_CELL_SIZE},  GRID_CELL_SIZE);}
                else if(m==3){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{(float)-GRID_CELL_SIZE,                    0.f},  GRID_CELL_SIZE);}
                else if(m==4){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{                   0.f, (float)-GRID_CELL_SIZE},  GRID_CELL_SIZE);}
                else if(m==5){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{(float)-GRID_CELL_SIZE, (float)-GRID_CELL_SIZE},  GRID_CELL_SIZE);}
                else if(m==6){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{(float) GRID_CELL_SIZE, (float)-GRID_CELL_SIZE},  GRID_CELL_SIZE);}
                else if(m==7){l = findNodeFromGrid(grid, particles[i].getPosition() - sf::Vector2f{(float)-GRID_CELL_SIZE, (float) GRID_CELL_SIZE},  GRID_CELL_SIZE);}
                
                if(l != -1 && l != j){
                    for(int k=0; k<grid[l].particles.size() && grid[l].particles[k]!=i; ++k){
            
                        sf::Vector2f direction = particles[grid[l].particles[k]].getPosition() - particles[i].getPosition();
                        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
                        
                        if(distance < minimumDistance && distance > 0){
                            acceleration[i] -= (minimumDistance - distance) * (direction/distance) * REPULSION_FACTOR;
                        }
                        else if(distance <= maximumDistance && distance >= minimumDistance){
                            acceleration[i] += (float)abs(log(distance)) * (direction/distance) * colorMatrix[color_row(i)][color_col(l,k)];
                        }
    
                    }
                }
            }
            acceleration[i] *= STRENGHT;
        }

    }

}