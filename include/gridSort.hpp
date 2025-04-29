#pragma once


#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern float maximumDistance;

struct Node{
    sf::Vector2f center;
    std::vector<int> particles;
};

void initGrid(std::vector<Node> &grid, int Width, int Height, int PARTICLE_RADIUS){

    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
    grid.clear();
    
    float gridSize = 20*PARTICLE_RADIUS;
    // float gridSize = maximumDistance;
    float gridWidth = Width / gridSize;
    float gridHeight = Height / gridSize;

    for(int i=0; i<gridWidth; ++i){
        grid.push_back(Node());
        for(int j=0; j<gridHeight; ++j){
            grid[i].center = {i*gridSize + (gridSize/2), j*gridSize + (gridSize/2)};
        }
    }
}

void cleanGrid(std::vector<Node> &grid){
    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
}


void insertGrid(sf::CircleShape* particles, sf::Vector2f* acceleration, std::vector<Node> &grid, int PARTICLE_COUNT, float gridSize){

    for(int i=0; i< PARTICLE_COUNT; ++i){

        for(int j=0; j<grid.size(); ++j){

            if(particles[i].getPosition().x < (grid[j].center.x + gridSize/2) && particles[i].getPosition().x > (grid[j].center.x - gridSize/2) && particles[i].getPosition().y < (grid[j].center.y + gridSize/2) && particles[i].getPosition().y > (grid[j].center.y - gridSize/2)){
                grid[j].particles.push_back(i);
                continue;
            }
        }
    }

}