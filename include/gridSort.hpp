#pragma once


#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern float maximumDistance;

struct Node{
    sf::Vector2f center;
    std::vector<int> particles;
};

void initGrid(std::vector<Node> &grid, int width, int height, float gridSize)
{
    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
    grid.clear();
    
    float gridWidth = width / gridSize;
    float gridHeight = height / gridSize;

    for(int i=0; i<gridWidth; ++i){
        for(int j=0; j<gridHeight; ++j){
            grid.push_back(Node());
            grid.back().center = {i*gridSize + (gridSize/2), j*gridSize + (gridSize/2)};
        }
    }
}

void cleanGrid(std::vector<Node> &grid)
{
    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
}

int findNodeFromGrid(std::vector<Node> &grid, sf::Vector2f position, int gridSize)
{
    for(int i=0; i<grid.size(); ++i){
        if(position.x < (grid[i].center.x + gridSize/2) && position.x >= (grid[i].center.x - gridSize/2) && position.y < (grid[i].center.y + gridSize/2) && position.y >= (grid[i].center.y - gridSize/2)){
            return i;
        }
    }
    return -1;
}


void insertGrid(sf::CircleShape* particles, sf::Vector2f* acceleration, std::vector<Node> &grid, int PARTICLE_COUNT, int gridSize)
{
    for(int i=0; i<PARTICLE_COUNT; ++i){

        int j = findNodeFromGrid(grid, particles[i].getPosition(), gridSize); 
        if(j != -1){
            grid[j].particles.push_back(i);
        }
    }

}